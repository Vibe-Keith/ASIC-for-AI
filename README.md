# ASIC-for-AI

Reverse-engineering the IceRiver KS-series Kaspa ASIC miners (Xilinx Zynq-7000
controller + kHeavyHash ASICs), with the research goal of understanding whether
the hardware exposes any path to the internal kHeavyHash matrix computation
(`M`, `v`, `M·v`) that could be repurposed as a matrix-multiply primitive.

## Current state

A clean-room forensic reconstruction of the **KS0 controller↔ASIC protocol**,
derived by data-flow from the stock `iceriverminer` binary. This supersedes an
earlier draft that contained several misidentifications (fixed and documented).

### Layout

| Path | Contents |
|---|---|
| `docs/KS0-ASIC-protocol-forensic-report.md` | The report — sections A–I: device/transport, frame format, command/response table, the corrected 8-byte read, full lifecycle call graph, single-board-test path, cross-model diffs, unexplained opcodes, and routes toward internal kHeavyHash state. |
| `ks0_protocol/ks0proto.py` | Standalone reference implementation: template parser, checksum, frame builder, job-frame builder, FPGA-FIFO de-mux, 13-byte RX frame parser, sensor decoders. Self-validates against firmware literals. |
| `ks0_protocol/examples.py` | Byte-for-byte worked examples (incl. the KS3 golden job frame round-trip). |
| `firmware/` | Vendored stock binaries (6 models), KS0 web-control source, startup script, boot log. See `firmware/SOURCE.md` for provenance + sha256. |
| `analysis/` | Gzipped Ghidra decompiles (6 models), raw `7F 55` command dumps per model, the key `scanhash` decompile, and the analysis scripts. |

### Headline findings (all proven from the binary; see report for evidence)

* **Transport:** ASIC bus is `/dev/spidev0.0` (SPI0, mode 0, 8-bit, ~20.8 MHz).
  `/dev/spidev1.0` is the **fan** controller; i2c-0/1 set PSU voltage. The tty/UART
  path in the binary is **dead code**.
* **Frame format:** `7F 55 | ADDR | CMD | LEN | PAYLOAD | CHK`, CHK = sum mod 256.
  Replies come back as 13-byte `55 7F …` frames reassembled from a Zynq-PL byte-FIFO.
* **The 8-byte `read()` is not a nonce** — it is one poll of that PL FIFO,
  4×(status,data), one byte per board.
* **Corrected reply opcodes:** `0x80` nonce-count+PLL, `0x81` temperature,
  `0x82` chip-model, `0x8E` voltage; found nonces arrive in a separate
  (bit7-clear) frame class, not via any read opcode.
* **"Single-board test" = normal mining init.** No distinct ASIC test command, no
  ASIC JTAG/BIST in firmware (only the Zynq PS boot JTAG, controller-side).
* **No digital path to `M`, `v`, `M·v`, or internal state.** The host sends only
  the 40-byte header; the ASIC regenerates and consumes the matrix internally.
  The matrix is, however, recomputable off-chip from public inputs.

### Reproduce

```sh
python3 ks0_protocol/ks0proto.py   # self-checks templates + job frame
python3 ks0_protocol/examples.py   # worked examples
```

Firmware here is community-published and analyzed for interoperability/security
research on hardware one owns; see `firmware/SOURCE.md`.
