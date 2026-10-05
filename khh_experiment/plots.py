"""Figures for the kHeavyHash representation + oracle experiments."""
import json
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from scipy import stats

# CVD-safe (Okabe-Ito subset); all bars carry direct labels (secondary encoding)
C = {"blue": "#0072B2", "verm": "#D55E00", "green": "#009E73",
     "orange": "#E69F00", "purple": "#CC79A7", "grey": "#777777"}
plt.rcParams.update({"figure.dpi": 130, "font.size": 10,
                     "axes.spines.top": False, "axes.spines.right": False,
                     "axes.grid": True, "grid.alpha": 0.25, "grid.linewidth": 0.6})

R = json.load(open("results.json"))


def best_acc(ds, rep):
    m = ds["reps"][rep]["models"]
    return max(m[k]["acc"] for k in m)


def fig_cascade():
    dsets = ["digits", "synth_linear", "moons64", "synth_xor"]
    reps = ["input", "raw_mv", "norm_mv", "pre_cshake", "final_bits", "final_bits_x16"]
    labels = ["input", "raw\nM·v", "norm\nM·v", "pre-\ncSHAKE", "final\n(cSHAKE)", "final\n×16 jobs"]
    cols = [C["blue"], C["green"], C["green"], C["orange"], C["verm"], C["verm"]]
    fig, axes = plt.subplots(1, 4, figsize=(15, 4.2), sharey=True)
    for ax, d in zip(axes, dsets):
        ds = R[d]
        vals = [best_acc(ds, r) for r in reps]
        ch = ds["chance_acc"]
        x = np.arange(len(reps))
        bars = ax.bar(x, vals, color=cols, width=0.72, zorder=3)
        for xi, v in zip(x, vals):
            ax.text(xi, v + 0.015, f"{v:.2f}", ha="center", va="bottom", fontsize=8)
        ax.axhline(ch, ls="--", lw=1.2, color=C["grey"], zorder=2)
        ax.text(len(reps) - 0.5, ch + 0.012, f"chance {ch:.2f}", ha="right",
                va="bottom", fontsize=8, color=C["grey"])
        ax.set_xticks(x); ax.set_xticklabels(labels, fontsize=8)
        ax.set_title(d, fontsize=11)
        ax.set_ylim(0, 1.05)
    axes[0].set_ylabel("best test accuracy (3 tiny models)")
    fig.suptitle("Task information survives M·v, collapses to chance at the final cSHAKE "
                 "(and stacking 16 jobs does not recover it)", fontsize=12)
    fig.tight_layout(rect=[0, 0, 1, 0.95])
    fig.savefig("fig1_accuracy_cascade.png", bbox_inches="tight")
    print("wrote fig1_accuracy_cascade.png")


def fig_stage_line():
    stages = ["input", "v", "raw_mv", "norm_mv", "pre_cshake", "final_bits"]
    names = ["input", "v (nibbles)", "raw M·v", "norm M·v", "pre-cSHAKE", "final cSHAKE"]
    fig, ax = plt.subplots(figsize=(8.2, 4.6))
    for d, col, mk in [("digits", C["blue"], "o"),
                       ("synth_linear", C["green"], "s"),
                       ("moons64", C["purple"], "^")]:
        ds = R[d]
        acc = [best_acc(ds, s) for s in stages]
        ax.plot(range(len(stages)), acc, "-", marker=mk, color=col, lw=2,
                markersize=7, label=d, zorder=3)
        ax.axhline(ds["chance_acc"], ls=":", lw=1, color=col, alpha=0.6)
    ax.axvspan(3.5, 5.5, color=C["verm"], alpha=0.07, zorder=0)
    ax.text(4.5, 0.12, "cSHAKE wall", ha="center", color=C["verm"], fontsize=10)
    ax.set_xticks(range(len(stages))); ax.set_xticklabels(names, rotation=20, fontsize=9)
    ax.set_ylabel("best test accuracy"); ax.set_ylim(0, 1.02)
    ax.set_title("Per-stage accuracy cascade (dotted = per-dataset chance)")
    ax.legend(frameon=False)
    fig.tight_layout(); fig.savefig("fig2_stage_cascade.png", bbox_inches="tight")
    print("wrote fig2_stage_cascade.png")


def fig_oracle():
    O = json.load(open("oracle_results.json"))
    rows = O["rows"]; N = O["config"]["N"]; p = O["config"]["p"]
    cls = np.array([r["cls"] for r in rows]); hits = np.array([r["hits"] for r in rows])
    uc = sorted(set(cls.tolist()))
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(12, 4.4))
    # panel 1: hit-count histograms by class + binomial pmf
    bins = np.arange(hits.min(), hits.max() + 2) - 0.5
    for c, col in zip(uc, [C["blue"], C["verm"]]):
        a1.hist(hits[cls == c], bins=bins, alpha=0.55, color=col, zorder=3,
                label=f"class {c} (rate {O['per_class_hit_rate'][str(c)]:.4f})")
    xs = np.arange(hits.min(), hits.max() + 1)
    a1.plot(xs, len(rows) / len(uc) * stats.binom.pmf(xs, N, p), color=C["grey"],
            lw=2, zorder=4, label=f"Binomial(N={N}, p={p:.4f})")
    a1.set_xlabel("hits per sample"); a1.set_ylabel("# samples")
    a1.set_title(f"Hit count by class vs input-independent Binomial\n"
                 f"(t-test p={O['hits_ttest']['p_value']:.2f} — no class dependence)")
    a1.legend(frameon=False, fontsize=8)
    # panel 2: MI permutation null
    rng = np.random.default_rng(7)
    from oracle import mutual_info_bits
    perm = np.array([mutual_info_bits(rng.permutation(cls), hits) for _ in range(1000)])
    a2.hist(perm, bins=30, color=C["grey"], alpha=0.6, zorder=3, label="MI null (label shuffled)")
    a2.axvline(O["mi_label_hits_bits"], color=C["verm"], lw=2.5, zorder=4,
               label=f"observed MI = {O['mi_label_hits_bits']:.3f} bits (p={O['mi_p_value']:.2f})")
    a2.set_xlabel("MI(label; hit-count)  [bits]"); a2.set_ylabel("permutations")
    a2.set_title("Mutual information with the label is indistinguishable from zero")
    a2.legend(frameon=False, fontsize=8)
    fig.suptitle("Black-box oracle  hit(x,nonce)=[kHeavyHash<target]  carries no label information",
                 fontsize=12)
    fig.tight_layout(rect=[0, 0, 1, 0.96])
    fig.savefig("fig3_oracle.png", bbox_inches="tight")
    print("wrote fig3_oracle.png")


if __name__ == "__main__":
    fig_cascade(); fig_stage_line(); fig_oracle()
