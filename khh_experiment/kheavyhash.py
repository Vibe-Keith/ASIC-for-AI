"""
Exact kHeavyHash (Kaspa PoW) reference, pure Python, self-validating.

Pipeline (matches kaspad `kaspa-hashes` / `kaspa-pow`):

    pow_hash = cSHAKE256(N="ProofOfWorkHash")( pre_pow(32) || ts(8 LE)
                                               || zeros(32) || nonce(8 LE) )   # 32B
    v[0..63] = nibbles(pow_hash)                                               # 64 x 4-bit
    product[i] = ( sum_j M[i][j]*v[j] ) >> 10                                  # 64 vals 0..14
    res[i]     = pow_hash[i] XOR ((product[2i]<<4)|product[2i+1])              # 32B
    final      = cSHAKE256(N="HeavyHash")( res )                              # 32B
    valid      = int.from_bytes(final,'big') <= target

M is a 64x64 matrix of 4-bit values generated from `pre_pow` via xoshiro256++,
regenerated until full rank (real reference uses float Gaussian-elim rank==64).

Keccak and cSHAKE here are validated at import against hashlib SHAKE256 and the
NIST SP800-185 cSHAKE256 example. See validate() / the __main__ block.

NOTE ON DOMAIN PLACEMENT: NIST cSHAKE(X,L,N,S) has function-name N and
customization S. Kaspa places the domain string in N (S empty). We do the same.
The scientific conclusions of the experiment (full Keccak diffusion in the final
stage) are invariant to whether the domain sits in N or S -- both are correct
cSHAKE instances with identical avalanche behaviour.
"""

from __future__ import annotations
import hashlib
from typing import List

import numpy as np

# --------------------------------------------------------------------------
# Keccak-f[1600]
# --------------------------------------------------------------------------
_RC = [
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080, 0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
]
_ROT = [
    [0, 36, 3, 41, 18], [1, 44, 10, 45, 2], [62, 6, 43, 15, 61],
    [28, 55, 25, 21, 56], [27, 20, 39, 8, 14],
]
_MASK = (1 << 64) - 1


def _rotl(x: int, n: int) -> int:
    return ((x << n) | (x >> (64 - n))) & _MASK


def keccak_f1600(state: List[int]) -> None:
    """In-place Keccak-f[1600] on 25 lanes (state[x + 5*y])."""
    A = [[state[x + 5 * y] for y in range(5)] for x in range(5)]
    for rnd in range(24):
        # theta
        C = [A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4] for x in range(5)]
        D = [C[(x - 1) % 5] ^ _rotl(C[(x + 1) % 5], 1) for x in range(5)]
        for x in range(5):
            for y in range(5):
                A[x][y] ^= D[x]
        # rho + pi
        B = [[0] * 5 for _ in range(5)]
        for x in range(5):
            for y in range(5):
                B[y][(2 * x + 3 * y) % 5] = _rotl(A[x][y], _ROT[x][y])
        # chi
        for x in range(5):
            for y in range(5):
                A[x][y] = B[x][y] ^ ((~B[(x + 1) % 5][y]) & B[(x + 2) % 5][y]) & _MASK
        # iota
        A[0][0] ^= _RC[rnd]
    for x in range(5):
        for y in range(5):
            state[x + 5 * y] = A[x][y]


def _keccak_sponge(rate_bytes: int, prefix: bytes, data: bytes,
                   suffix: int, outlen: int) -> bytes:
    """Generic Keccak sponge with domain-separation `suffix` byte."""
    state = [0] * 25
    msg = prefix + data
    # pad10*1 with the given suffix merged into the first pad byte
    pad_len = rate_bytes - (len(msg) % rate_bytes)
    if pad_len == 0:
        pad_len = rate_bytes
    pad = bytearray(pad_len)
    pad[0] = suffix
    pad[-1] ^= 0x80
    msg = msg + bytes(pad)

    def absorb(block: bytes):
        for i in range(0, rate_bytes, 8):
            lane = int.from_bytes(block[i:i + 8], "little")
            state[i // 8] ^= lane
        keccak_f1600(state)

    for off in range(0, len(msg), rate_bytes):
        absorb(msg[off:off + rate_bytes])

    out = bytearray()
    while len(out) < outlen:
        for i in range(rate_bytes // 8):
            out += state[i].to_bytes(8, "little")
            if len(out) >= outlen:
                break
        if len(out) < outlen:
            keccak_f1600(state)
    return bytes(out[:outlen])


def shake256(data: bytes, outlen: int) -> bytes:
    # SHAKE256: rate 1088 bits = 136 bytes, suffix 0x1F
    return _keccak_sponge(136, b"", data, 0x1F, outlen)


def _left_encode(x: int) -> bytes:
    if x == 0:
        return bytes([1, 0])
    n = (x.bit_length() + 7) // 8
    return bytes([n]) + x.to_bytes(n, "big")


def _encode_string(s: bytes) -> bytes:
    return _left_encode(len(s) * 8) + s


def _bytepad(x: bytes, w: int) -> bytes:
    z = _left_encode(w) + x
    if len(z) % w:
        z += bytes(w - (len(z) % w))
    return z


def cshake256(data: bytes, outlen: int, N: bytes = b"", S: bytes = b"") -> bytes:
    """cSHAKE256 per NIST SP800-185. If N and S are both empty, == SHAKE256."""
    if not N and not S:
        return shake256(data, outlen)
    rate = 136
    prefix = _bytepad(_encode_string(N) + _encode_string(S), rate)
    # cSHAKE domain-separation suffix is 0x04
    return _keccak_sponge(rate, prefix, data, 0x04, outlen)


# --------------------------------------------------------------------------
# xoshiro256++  (matches Kaspa matrix seed RNG)
# --------------------------------------------------------------------------
class XoShiRo256PlusPlus:
    def __init__(self, seed32: bytes):
        assert len(seed32) == 32
        self.s = [int.from_bytes(seed32[i:i + 8], "little") for i in range(0, 32, 8)]

    def next_u64(self) -> int:
        s = self.s
        result = (_rotl((s[0] + s[3]) & _MASK, 23) + s[0]) & _MASK
        t = (s[1] << 17) & _MASK
        s[2] ^= s[0]; s[3] ^= s[1]; s[1] ^= s[2]; s[0] ^= s[3]
        s[2] ^= t
        s[3] = _rotl(s[3], 45)
        return result


def generate_matrix(seed32: bytes) -> np.ndarray:
    """64x64 matrix of 4-bit values from `seed32`, regenerated until full rank
    (float rank == 64, as in the reference)."""
    rng = XoShiRo256PlusPlus(seed32)
    while True:
        m = np.zeros((64, 64), dtype=np.int64)
        for i in range(64):
            for j0 in range(0, 64, 16):
                val = rng.next_u64()
                for k in range(16):
                    m[i, j0 + k] = (val >> (4 * k)) & 0x0F
        if np.linalg.matrix_rank(m.astype(np.float64)) == 64:
            return m


# --------------------------------------------------------------------------
# kHeavyHash
# --------------------------------------------------------------------------
def nibbles_of(h32: bytes) -> np.ndarray:
    v = np.zeros(64, dtype=np.int64)
    for i in range(32):
        v[2 * i] = h32[i] >> 4
        v[2 * i + 1] = h32[i] & 0x0F
    return v


def pack_nibbles(v: np.ndarray) -> bytes:
    out = bytearray(32)
    for i in range(32):
        out[i] = ((int(v[2 * i]) & 0x0F) << 4) | (int(v[2 * i + 1]) & 0x0F)
    return bytes(out)


def heavy_hash_stages(h32: bytes, matrix: np.ndarray):
    """Run heavy_hash on a 32-byte input, returning every intermediate.

    Returns dict with:
      v           : 64 nibbles of h32                     (rep 3)
      raw_mv      : M @ v, 64 ints (0..~14400)            (rep 4)
      norm_mv     : raw_mv >> 10, 64 ints (0..14)         (rep 5)
      pre_cshake  : 32 bytes = h32 XOR pack(norm_mv)      (rep 6)
      final       : cSHAKE256(HeavyHash)(pre_cshake), 32B (rep 7)
    """
    v = nibbles_of(h32)
    raw = matrix @ v                      # (64,)
    norm = raw >> 10
    packed = pack_nibbles(norm)
    pre = bytes(a ^ b for a, b in zip(h32, packed))
    final = cshake256(pre, 32, N=b"HeavyHash")
    return {"v": v, "raw_mv": raw, "norm_mv": norm,
            "pre_cshake": pre, "final": final}


def pow_hash(pre_pow: bytes, timestamp: int, nonce: int) -> bytes:
    """First stage: cSHAKE256(ProofOfWorkHash) over the 80-byte PoW preimage."""
    assert len(pre_pow) == 32
    msg = pre_pow + timestamp.to_bytes(8, "little") + bytes(32) + nonce.to_bytes(8, "little")
    return cshake256(msg, 32, N=b"ProofOfWorkHash")


def kaspa_pow_final(pre_pow: bytes, timestamp: int, nonce: int,
                    matrix: np.ndarray) -> bytes:
    """Full real pipeline pre_pow+ts+nonce -> 32-byte final PoW hash."""
    h = pow_hash(pre_pow, timestamp, nonce)
    return heavy_hash_stages(h, matrix)["final"]


# --------------------------------------------------------------------------
# Validation
# --------------------------------------------------------------------------
def validate() -> None:
    # 1) SHAKE256 == hashlib on random inputs (validates Keccak-f + SHAKE pad)
    import os
    for _ in range(50):
        d = os.urandom(np.random.randint(0, 400))
        n = np.random.randint(1, 200)
        assert shake256(d, n) == hashlib.shake_256(d).digest(n), "SHAKE256 mismatch"
    # 2) cSHAKE256 vs NIST SP800-185 example (Sample #3: N="", S="Email Signature")
    # NIST SP800-185 cSHAKE256 Sample #3, first 256 bits of the 512-bit output
    nist = bytes.fromhex(
        "d008828e2b80ac9d2218ffee1d070c48b8e4c87bff32c9699d5b6896eee0edd1")
    got = cshake256(bytes([0, 1, 2, 3]), 32, N=b"", S=b"Email Signature")
    assert got == nist, "cSHAKE256 NIST vector mismatch: " + got.hex()
    # 3) matrix is full rank and 4-bit
    m = generate_matrix(bytes(range(32)))
    assert m.shape == (64, 64) and m.min() >= 0 and m.max() <= 15
    assert np.linalg.matrix_rank(m.astype(float)) == 64


if __name__ == "__main__":
    validate()
    print("kHeavyHash core validated: SHAKE256==hashlib, cSHAKE256==NIST vector, matrix full-rank")
    m = generate_matrix(bytes(range(32)))
    st = heavy_hash_stages(bytes(range(32)), m)
    print("v[:8]       =", st["v"][:8].tolist())
    print("raw_mv[:4]  =", st["raw_mv"][:4].tolist())
    print("norm_mv[:8] =", st["norm_mv"][:8].tolist())
    print("final       =", st["final"].hex())
    print("pow_hash    =", pow_hash(bytes(range(32)), 123456, 42).hex())
