"""
Experiment B: does task-relevant structure survive each stage of kHeavyHash?

For each dataset and each representation we train the SAME family of tiny models
on the SAME split and report accuracy/F1/AUC (classification), RMSE/R2
(regression), dimensionality, and train/infer time.

Representations (all derived from the EXACT kHeavyHash, kheavyhash.py):
  input     : original features (baseline)
  v         : 4-bit quantization of features -> the 64-nibble vector v (rep 3)
  raw_mv    : M @ v, fixed job matrix M                               (rep 4)
  norm_mv   : raw_mv >> 10                                            (rep 5)
  pre_cshake: 32 bytes (h XOR pack(norm_mv)) expanded to 256 bits     (rep 6)
  final     : cSHAKE256(HeavyHash)(pre_cshake) -> 256 bits            (rep 7)
  final_bits/byte variants + multi-job stacking handled in run_all().

Injection: input x -> v (nibble quantize). The 32-byte h fed to heavy_hash is
pack(v); i.e. we evaluate the exact heavy_hash() function with the input playing
the role of the hash. This isolates what the matrix step and the final cSHAKE do
to information about the input. Everything is used strictly as a BLACK-BOX
feature (no gradients through cSHAKE), which is the only thing a real ASIC could
ever provide.
"""
from __future__ import annotations
import time, json, hashlib
import numpy as np
from dataclasses import dataclass, field

from sklearn.datasets import load_digits, make_classification, make_moons
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression, Ridge
from sklearn.neighbors import KNeighborsClassifier, KNeighborsRegressor
from sklearn.neural_network import MLPClassifier, MLPRegressor
from sklearn.metrics import (accuracy_score, f1_score, roc_auc_score,
                             mean_squared_error, r2_score)

from kheavyhash import generate_matrix, heavy_hash_stages, pack_nibbles

RNG = np.random.default_rng(0)
JOB_SEEDS = [bytes([s]) * 32 for s in range(1, 17)]   # independent job matrices
_MATRIX_CACHE: dict[bytes, np.ndarray] = {}


def job_matrix(seed32: bytes) -> np.ndarray:
    if seed32 not in _MATRIX_CACHE:
        _MATRIX_CACHE[seed32] = generate_matrix(seed32)
    return _MATRIX_CACHE[seed32]


def to_nibbles(X: np.ndarray) -> np.ndarray:
    """Scale each feature to 0..15 integer nibbles (per-column min-max)."""
    lo = X.min(0, keepdims=True); hi = X.max(0, keepdims=True)
    rng = np.where(hi > lo, hi - lo, 1.0)
    q = np.round((X - lo) / rng * 15).astype(np.int64)
    return np.clip(q, 0, 15)


def pad_to_64(V: np.ndarray) -> np.ndarray:
    """Tile/trim a nibble matrix to exactly 64 columns."""
    n, d = V.shape
    if d == 64:
        return V
    reps = int(np.ceil(64 / d))
    return np.tile(V, (1, reps))[:, :64]


def bytes_to_bits(b: bytes) -> np.ndarray:
    return np.unpackbits(np.frombuffer(b, dtype=np.uint8))


def build_representations(Xnib64: np.ndarray, job_seeds) -> dict:
    """Return {rep_name: feature_matrix} for one dataset.

    Single-job reps use job_seeds[0]. Multi-job reps concatenate across seeds.
    """
    n = Xnib64.shape[0]
    reps: dict[str, np.ndarray] = {}
    reps["input"] = Xnib64.astype(np.float64)          # (n,64) nibble input == v
    reps["v"] = Xnib64.astype(np.float64)              # identical here by design

    # single fixed job
    M0 = job_matrix(job_seeds[0])
    raw = np.zeros((n, 64)); norm = np.zeros((n, 64))
    pre_bits = np.zeros((n, 256)); fin_bits = np.zeros((n, 256))
    fin_bytes = np.zeros((n, 32))
    for i in range(n):
        h = pack_nibbles(Xnib64[i])
        st = heavy_hash_stages(h, M0)
        raw[i] = st["raw_mv"]; norm[i] = st["norm_mv"]
        pre_bits[i] = bytes_to_bits(st["pre_cshake"])
        fb = st["final"]
        fin_bits[i] = bytes_to_bits(fb)
        fin_bytes[i] = np.frombuffer(fb, dtype=np.uint8)
    reps["raw_mv"] = raw
    reps["norm_mv"] = norm
    reps["pre_cshake"] = pre_bits
    reps["final_bits"] = fin_bits
    reps["final_bytes"] = fin_bytes

    # multi-job stacking: K independent matrices
    for K in (4, 16):
        normK = []; finK = []
        for s in job_seeds[:K]:
            Mk = job_matrix(s)
            nm = np.zeros((n, 64)); fb = np.zeros((n, 256))
            for i in range(n):
                st = heavy_hash_stages(pack_nibbles(Xnib64[i]), Mk)
                nm[i] = st["norm_mv"]; fb[i] = bytes_to_bits(st["final"])
            normK.append(nm); finK.append(fb)
        reps[f"norm_mv_x{K}"] = np.concatenate(normK, axis=1)
        reps[f"final_bits_x{K}"] = np.concatenate(finK, axis=1)
    return reps


# --------------------------------------------------------------------------
# model family
# --------------------------------------------------------------------------
def eval_classification(Xtr, Xte, ytr, yte) -> dict:
    scaler = StandardScaler().fit(Xtr)
    Xtr_s, Xte_s = scaler.transform(Xtr), scaler.transform(Xte)
    models = {
        "logreg": LogisticRegression(max_iter=2000, C=1.0),
        "knn": KNeighborsClassifier(n_neighbors=5),
        "mlp": MLPClassifier(hidden_layer_sizes=(64,), max_iter=400,
                             early_stopping=True, random_state=0),
    }
    out = {}
    ncls = len(np.unique(ytr))
    for name, mdl in models.items():
        t0 = time.perf_counter(); mdl.fit(Xtr_s, ytr); ttr = time.perf_counter() - t0
        t0 = time.perf_counter(); pred = mdl.predict(Xte_s); tin = time.perf_counter() - t0
        acc = accuracy_score(yte, pred)
        f1 = f1_score(yte, pred, average="macro")
        auc = np.nan
        try:
            if hasattr(mdl, "predict_proba"):
                proba = mdl.predict_proba(Xte_s)
                auc = (roc_auc_score(yte, proba[:, 1]) if ncls == 2
                       else roc_auc_score(yte, proba, multi_class="ovr"))
        except Exception:
            pass
        out[name] = dict(acc=acc, f1=f1, auc=auc,
                         train_s=ttr, infer_s=tin)
    return out


def eval_regression(Xtr, Xte, ytr, yte) -> dict:
    scaler = StandardScaler().fit(Xtr)
    Xtr_s, Xte_s = scaler.transform(Xtr), scaler.transform(Xte)
    models = {
        "ridge": Ridge(alpha=1.0),
        "knn": KNeighborsRegressor(n_neighbors=5),
        "mlp": MLPRegressor(hidden_layer_sizes=(64,), max_iter=400,
                            early_stopping=True, random_state=0),
    }
    out = {}
    for name, mdl in models.items():
        t0 = time.perf_counter(); mdl.fit(Xtr_s, ytr); ttr = time.perf_counter() - t0
        t0 = time.perf_counter(); pred = mdl.predict(Xte_s); tin = time.perf_counter() - t0
        rmse = float(np.sqrt(mean_squared_error(yte, pred)))
        out[name] = dict(rmse=rmse, r2=r2_score(yte, pred),
                         train_s=ttr, infer_s=tin)
    return out


def retrieval_precision_at_k(Xtr, Xte, ytr, yte, k=5) -> float:
    """Pure similarity probe: for each test point, fraction of its k nearest
    TRAIN neighbours (euclidean, standardized) sharing its label."""
    sc = StandardScaler().fit(Xtr)
    A, B = sc.transform(Xte), sc.transform(Xtr)
    # chunked distances to bound memory
    hits = 0; tot = 0
    for i in range(A.shape[0]):
        d = np.sum((B - A[i]) ** 2, axis=1)
        idx = np.argpartition(d, k)[:k]
        hits += np.sum(ytr[idx] == yte[i]); tot += k
    return hits / tot


# --------------------------------------------------------------------------
# datasets
# --------------------------------------------------------------------------
def datasets():
    out = {}

    # 1) sklearn digits: 8x8 = 64 features natively -> maps directly onto v
    dig = load_digits()
    out["digits"] = (dig.data, dig.target, "clf")

    # 2) synthetic LINEAR / similarity-structured: well-separated gaussian blobs,
    #    linearly separable; nearest-neighbour works; known structure.
    Xs, ys = make_classification(n_samples=2000, n_features=64, n_informative=20,
                                 n_redundant=10, n_classes=4, class_sep=2.0,
                                 random_state=0)
    out["synth_linear"] = (Xs, ys, "clf")

    # 3) synthetic NONLINEAR: XOR-in-high-dim; label = parity of signs of 2
    #    informative dims -> NOT linearly separable, needs nonlinearity.
    Z = RNG.standard_normal((2000, 64))
    y_xor = ((Z[:, 0] > 0) ^ (Z[:, 1] > 0)).astype(int)
    out["synth_xor"] = (Z, y_xor, "clf")

    # 4) two-moons embedded in 64-d (similarity matters, mild nonlinearity)
    Xm, ym = make_moons(n_samples=2000, noise=0.2, random_state=0)
    pad = RNG.standard_normal((2000, 62)) * 0.1
    out["moons64"] = (np.concatenate([Xm, pad], axis=1), ym, "clf")

    # 5) synthetic REGRESSION: smooth nonlinear target of a few features
    Xr = RNG.uniform(-1, 1, (2000, 64))
    yr = (np.sin(3 * Xr[:, 0]) + Xr[:, 1] ** 2 - 0.5 * Xr[:, 2] * Xr[:, 3])
    out["synth_regression"] = (Xr, yr, "reg")
    return out


def run_all(path="results.json"):
    results = {}
    for dname, (X, y, kind) in datasets().items():
        Xnib = pad_to_64(to_nibbles(X))
        reps = build_representations(Xnib, JOB_SEEDS)
        strat = y if kind == "clf" else None
        idx_tr, idx_te = train_test_split(np.arange(len(y)), test_size=0.3,
                                          random_state=0, stratify=strat)
        ds = {"kind": kind, "n": int(len(y)),
              "n_classes": int(len(np.unique(y))) if kind == "clf" else None,
              "reps": {}}
        for rname, F in reps.items():
            Xtr, Xte = F[idx_tr], F[idx_te]
            ytr, yte = y[idx_tr], y[idx_te]
            entry = {"dim": int(F.shape[1])}
            if kind == "clf":
                entry["models"] = eval_classification(Xtr, Xte, ytr, yte)
                entry["retrieval_p@5"] = retrieval_precision_at_k(Xtr, Xte, ytr, yte)
            else:
                entry["models"] = eval_regression(Xtr, Xte, ytr, yte)
            ds["reps"][rname] = entry
            print(f"[{dname}] {rname:16s} done (dim={F.shape[1]})")
        # chance baselines
        if kind == "clf":
            _, cnt = np.unique(y[idx_te], return_counts=True)
            ds["chance_acc"] = float(cnt.max() / cnt.sum())
        else:
            ds["var_test"] = float(np.var(y[idx_te]))
        results[dname] = ds
        print(f"=== dataset {dname} complete ===")
    with open(path, "w") as f:
        json.dump(results, f, indent=2)
    print("wrote", path)
    return results


if __name__ == "__main__":
    run_all()
