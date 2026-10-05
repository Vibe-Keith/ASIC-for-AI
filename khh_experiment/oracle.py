"""
Black-box predicate oracle experiment.

Treat the ASIC as   hit(x, nonce) := [ kHeavyHash(header(x), nonce) <= target ].
Question: does the distribution of hits / nonce values / search time encode the
label of x beyond ordinary random sampling?

We derive a distinct job (matrix + 40-byte header) from each input x, run a real
kHeavyHash nonce sweep, and record per-sample oracle statistics:
  hits          : count of nonces with final <= target  (Binomial(N,p))
  first_hit     : index of first hit                     (Geometric(p))
  mean/std nonce: distribution of hitting nonces
Then we test whether any of these depends on the class label.

Everything uses the EXACT validated kHeavyHash (kheavyhash.py).
"""
from __future__ import annotations
import time, json, hashlib
import numpy as np
from scipy import stats

from kheavyhash import generate_matrix, pow_hash, heavy_hash_stages
from sklearn.datasets import load_digits

RNG = np.random.default_rng(1)


def header_from_input(x: np.ndarray):
    """Deterministic (pre_pow, timestamp, matrix) from an input vector."""
    h = hashlib.sha256(x.tobytes()).digest()          # 32-byte pre_pow seed
    ts = int.from_bytes(h[:8], "little") & 0xffffffff
    M = generate_matrix(h)                             # job matrix from seed
    return h, ts, M


def final_int(pre_pow, ts, nonce, M) -> int:
    hpow = pow_hash(pre_pow, ts, nonce)
    fin = heavy_hash_stages(hpow, M)["final"]
    return int.from_bytes(fin, "big")


def run_oracle(samples_per_class=30, classes=(0, 1), N=2500,
               p=1.0 / 64, path="oracle_results.json"):
    target = int(p * (1 << 256))
    dig = load_digits()
    rows = []
    t0 = time.perf_counter()
    for c in classes:
        idx = np.where(dig.target == c)[0][:samples_per_class]
        for si in idx:
            x = dig.data[si].astype(np.float64)
            pre, ts, M = header_from_input(x)
            hits = 0; first = -1; hit_nonces = []
            for nonce in range(N):
                if final_int(pre, ts, nonce, M) <= target:
                    hits += 1
                    if first < 0:
                        first = nonce
                    hit_nonces.append(nonce)
            rows.append(dict(cls=int(c), hits=hits,
                             first=(first if first >= 0 else N),
                             mean_nonce=float(np.mean(hit_nonces)) if hit_nonces else -1.0,
                             n_hit=len(hit_nonces)))
        print(f"class {c}: done {samples_per_class} samples "
              f"({time.perf_counter()-t0:.0f}s elapsed)")
    res = analyze(rows, N, p, target)
    res["config"] = dict(samples_per_class=samples_per_class, classes=list(classes),
                         N=N, p=p, calls=len(rows) * N,
                         seconds=time.perf_counter() - t0)
    res["rows"] = rows
    with open(path, "w") as f:
        json.dump(res, f, indent=2)
    print("wrote", path)
    return res


def mutual_info_bits(labels, values, n_bins=8) -> float:
    """Empirical MI(label; binned value) with Miller-Madow correction, in bits."""
    labels = np.asarray(labels); values = np.asarray(values, dtype=float)
    edges = np.quantile(values, np.linspace(0, 1, n_bins + 1))
    edges[-1] += 1e-9
    b = np.clip(np.digitize(values, edges[1:-1]), 0, n_bins - 1)
    mi = 0.0
    n = len(labels)
    for lv in np.unique(labels):
        for bv in np.unique(b):
            p_lb = np.mean((labels == lv) & (b == bv))
            if p_lb <= 0:
                continue
            p_l = np.mean(labels == lv); p_b = np.mean(b == bv)
            mi += p_lb * np.log2(p_lb / (p_l * p_b))
    # Miller-Madow bias correction
    cells = len(np.unique(labels)) * len(np.unique(b))
    mi -= (cells - 1) / (2 * n * np.log(2))
    return mi


def analyze(rows, N, p, target) -> dict:
    cls = np.array([r["cls"] for r in rows])
    hits = np.array([r["hits"] for r in rows])
    first = np.array([r["first"] for r in rows])
    out = {}
    uc = np.unique(cls)
    # per-class hit rate
    out["hit_rate_overall"] = float(hits.sum() / (len(rows) * N))
    out["expected_p"] = p
    out["per_class_hit_rate"] = {int(c): float(hits[cls == c].sum()
                                               / (np.sum(cls == c) * N)) for c in uc}
    # Welch t-test: does hit count differ by class?
    g = [hits[cls == c] for c in uc]
    if len(uc) == 2:
        t, pv = stats.ttest_ind(g[0], g[1], equal_var=False)
        out["hits_ttest"] = dict(t=float(t), p_value=float(pv))
        tf, pf = stats.ttest_ind(first[cls == uc[0]], first[cls == uc[1]],
                                 equal_var=False)
        out["firsthit_ttest"] = dict(t=float(tf), p_value=float(pf))
    # chi-square: are hit counts consistent with a SINGLE binomial (no class dep)?
    # compare observed hit-count variance to binomial N*p*(1-p)
    out["hits_mean"] = float(hits.mean())
    out["hits_var_observed"] = float(hits.var())
    out["hits_var_binomial"] = float(N * p * (1 - p))
    # MI(label; hits) with permutation null
    mi_obs = mutual_info_bits(cls, hits)
    perm = []
    rng = np.random.default_rng(7)
    for _ in range(500):
        perm.append(mutual_info_bits(rng.permutation(cls), hits))
    perm = np.array(perm)
    out["mi_label_hits_bits"] = float(mi_obs)
    out["mi_permutation_mean_bits"] = float(perm.mean())
    out["mi_permutation_p95_bits"] = float(np.quantile(perm, 0.95))
    out["mi_p_value"] = float(np.mean(perm >= mi_obs))
    # KS test: are hitting-nonce means uniform-consistent across classes?
    mn = np.array([r["mean_nonce"] for r in rows if r["n_hit"] > 0])
    mncls = np.array([r["cls"] for r in rows if r["n_hit"] > 0])
    if len(np.unique(mncls)) == 2 and len(mn) > 4:
        ks, ksp = stats.ks_2samp(mn[mncls == uc[0]], mn[mncls == uc[1]])
        out["meannonce_ks"] = dict(stat=float(ks), p_value=float(ksp))
    # sample-complexity bound: given the OBSERVED between-class rate gap, how many
    # nonces would be needed to distinguish classes at 95%/80% power?
    rates = out["per_class_hit_rate"]
    if len(uc) == 2:
        d = abs(rates[int(uc[0])] - rates[int(uc[1])])
        out["observed_rate_gap"] = d
        if d > 0:
            # N per sample ~ (z_a+z_b)^2 * 2 p(1-p) / d^2  (two-proportion)
            out["N_needed_for_gap"] = float((1.96 + 0.84) ** 2 * 2 * p * (1 - p) / d ** 2)
        else:
            out["N_needed_for_gap"] = float("inf")
    return out


if __name__ == "__main__":
    res = run_oracle()
    import pprint
    pr = {k: v for k, v in res.items() if k != "rows"}
    pprint.pprint(pr)
