# IceRiver KS0 — Clean-Room Forensic Reconstruction of the Controller↔ASIC Path

Scope: the stock KS0 miner, `firmware/binaries/iceriverminer-KS0`
(ELF32 ARM EABI5 hard-float, Thumb-2, stripped; BuildID
`71a5a3420f7fcb5e682ccae4c0b3abb10cf3d067`; sha256
`f3b9adf9740c7616c0060e2b44fe4416e256c54113cb9297bd9d09b346f08767`).
Controller SoC is a Xilinx Zynq-7000 (ARM Cortex-A9, kernel
`4.19.0-xilinx-v2019.2`, machine `xlnx,zynq-7000` — see `firmware/OS/dmesg-KS3L.txt`).

All function labels (`FUN_xxxxxxxx`) are virtual addresses in the KS0 binary.
Evidence classes are tagged **PROVEN** (direct code/`.rodata` data-flow),
**STRONGLY INDICATED** (multiple independent binary clues), **SPECULATIVE**
(needs hardware). This report discards the previous reconstruction and
re-derives everything.

> **Corrections to the earlier analysis (all now re-proven below):**
> 1. ASIC link is `/dev/spidev0.0`. `/dev/spidev1.0` is the **fan** controller.
> 2. The tty/UART path and the `09 01 0x` sleep/wake frames are **dead code** in KS0.
> 3. The 8-byte `read()` is **not** a nonce — it is one poll of the PL RX byte-FIFO.
> 4. `0x80/0x82/0x8E` meanings were wrong; re-proven in section C.

---

## A. Device / transport identification (PROVEN)

The ASIC call graph touches four kernel devices. Each was traced from `open()`
forward to its ioctls/callers.

| Device | Opened by | ioctls / use | Role |
|---|---|---|---|
| `/dev/spidev0.0` | `FUN_001169f4(bus=0,cs=0,40 MHz,mode=0x0C,8bit)` ← `FUN_00116ca8` "init first" | `SPI_IOC_WR/RD_MODE` `0x40016b01/0x80016b01`, `_BITS_PER_WORD` `..6b03`, `_MAX_SPEED_HZ` `..6b04` | **ASIC bus** (host side) |
| `/dev/spidev1.0` | `FUN_00127ed4` ← `FUN_00127ffc` `printf("set fan %02x")` | writes a 10-byte fan record | **Fan controller** — not ASIC |
| `/dev/i2c-0`, `/dev/i2c-1` | `FUN_00126f14`/`FUN_00127188` | `Set V 9512`, `Set V bdp` (`FUN_00121ff4`) | **PSU / board power** (voltage set) |
| `/sys/class/gpio/gpio*` | `FUN_00127914` (set), `FUN_00127aa4` (get), `FUN_001278bc` (edge) | EMIO lines, see §E | reset / channel-select / FIFO strobe |

**Why `spidev0.0` is the ASIC bus (not inferred from names):**
`FUN_00116ca8` opens it via `FUN_001169f4`, immediately runs the ASIC bring-up
`FUN_0011b59c` (`proto_init_cmd`) on the returned fd, and the same fd is the one
every `7F 55` frame and every nonce/status byte flows through. Disassembly at
`0x116cf8` sets `r0=0 (bus), r1=0 (cs), r2=0x2625A00 (40 000 000), [sp]=8,
r3=0x0C` → `sprintf("/dev/spidev%d.%d",0,0)`. The KS3L boot log corroborates the
hardware: `spidev spi0.0: ... mode 0, 8 bits/w, 20833333 clock speed` (the
Cadence SPI clamps the requested 40 MHz to ~20.83 MHz). SPI1 (`spi1.0`) is a
separate master; `FUN_00127ffc` writes fan PWM records to it.

**Dead code (PROVEN):** the tty path — `FUN_0011a658` (`open(O_RDWR|NOCTTY|
NONBLOCK)` + `isatty`), `FUN_0011a6a4` (`Configure UART done.` termios, 1 Mbaud
table), `FUN_0011be0c` (`open uart succ!`), `FUN_0011bf44` (`uart_read:`),
`FUN_0011bd04` (`read global temp`) — has **no callers** and **no pointer
references**. The `7F 55 FF 09 01 01/00` sleep/wake frames (`.rodata`
`0x17e448/0x17e460`) likewise have **no references** anywhere in the binary.
The ASIC transport is SPI0 only. (The `0b 02 00 19` "switch uart to 1M" frame is
still sent — but that configures the *ASIC's own* serial side; the host keeps
talking SPI.)

---

## B. Proven frame format

### B.1 Host → ASIC

```
+------+------+------+------+------+-----------------+------+
| 0x7F | 0x55 | ADDR | CMD  | LEN  | PAYLOAD[LEN]    | CHK  |
+------+------+------+------+------+-----------------+------+
   0      1      2      3      4      5 .. 5+LEN-1    5+LEN
```

* **Preamble** `7F 55`, fixed.
* **ADDR** chip address. `0xFF` = broadcast; `0x00` = "unassigned" (only the
  `0x02` address-assignment frame uses `0x00`).
* **CMD** opcode. Bit 7 is **not** meaningful on the TX side (that convention is
  RX-only, §B.2).
* **LEN** payload length in bytes.
* **PAYLOAD** `LEN` bytes.
* **CHK** = `sum(all preceding bytes) & 0xFF`.

**Checksum (PROVEN, `FUN_0011af7c` + inlined SWAR copies in `FUN_0011acbc`/
`FUN_0011b1b0`).** The firmware accumulates per-byte-lane across 32-bit words
`((a&0x7f7f7f7f)+(b&0x7f7f7f7f)) ^ ((a^b)&0x80808080)` then folds the four lanes.
That is exactly `sum(bytes) & 0xFF`. Verified against five independent literals
in `ks0_protocol/examples.py`.

**Template → bytes (PROVEN).** Frames live in `.rodata` as ASCII like
`"7f 55 ff 81 01 00"`. The loop `for(i=0;i<strlen;i+=3) buf[i/3]=strtoul(s+i,0,16)`
converts them; `strtoul` skips whitespace so the double space in
`"7f 55 ff 8e  01 30"` still yields 6 bytes.

**Two ways CHK reaches the wire** (both produce the same format):
* via `FUN_0011acbc` (all init frames) and `FUN_0011b1b0(...,flag=1)` — the code
  **appends** `sum&0xFF`. The literal's LEN already covers the whole payload
  (e.g. literal `..09 08 ...07 D0 8A` is 8 payload bytes; CHK `0x51` is appended).
* via `FUN_0011b1b0(...,flag=0)` — sent verbatim; here the CHK is already written
  into the literal string (only the `0x80` query does this: trailing `0x59`).

There is **no escaping/stuffing**. Inter-frame delay is `usleep(15000)` after
every write (`usleep(15000)` tail in `FUN_0011acbc`/`FUN_0011b1b0`); the address
sweep adds an extra `usleep(1000)`.

### B.2 ASIC → host — a 13-byte frame carried over a PL byte-FIFO

The ASIC's replies do **not** come back as SPI read payloads of a request.
Instead the Zynq **PL** (FPGA fabric) buffers each board's incoming ASIC serial
stream into a FIFO, and the host drains it byte-at-a-time by writing a fixed
10-byte poll token and reading 8 bytes (§D). Software then reassembles 13-byte
frames from each board's byte stream (`FUN_001143a8` ring-buffer scan):

```
+------+------+----+----+----+----+----+----+----+----+------+------+------+
| 0x55 | 0x7F | b2 | b3 | b4 | b5 | b6 | b7 | b8 | b9 | b10  | RTYP | CHK  |
+------+------+----+----+----+----+----+----+----+----+------+------+------+
   0      1     2    3    4    5    6    7    8    9    10     11     12
```

* Preamble is **`55 7F`** — byte order **reversed** vs TX.
* `CHK` (byte 12) = `sum(bytes 0..11) & 0xFF` (`FUN_0011af7c(&buf,0x0C)`).
* **`RTYP`** (byte 11) dispatch:
  * **bit7 = 1** → status/query reply; byte 10 = chip address; subtype in
    `{0x80,0x81,0x82,0x8E}` (§C).
  * **bit7 = 0** → **found-nonce** result (§D).

---

## C. Command / response table (only opcodes the KS0 firmware actually uses)

### C.1 Host → ASIC (PROVEN)

| CMD | Example wire bytes | Sent by | Meaning (from context/handler) |
|---|---|---|---|
| `0x01` | `7F 55 FF 01 01 00 D5` | `FUN_0011b59c` | broadcast reset/enable (first frame after RSTN) |
| `0x02` | `7F 55 00 02 01 <a> ..` | `FUN_0011b59c` | assign chip address `<a>` (ADDR=0x00) |
| `0x0B` | `7F 55 FF 0B 02 00 19 F9` | `FUN_0011b59c` | set ASIC serial side to 1 Mbaud |
| `0x07` | `7F 55 FF 07 04 <mask4>` | `FUN_0011b59c` | core-enable walking mask |
| `0x09` | `7F 55 FF 09 08 01 0B 00 00 00 07 D0 8A 51` | `FUN_0011b59c`, `FUN_00116684/7fc` | PLL / frequency (field `07 D0`; per-chip at runtime) |
| `0x05` | `7F 55 FF 05 03 C3 AC 3A 84` | `FUN_0011b59c` | timing/config constant |
| `0x0D` | `7F 55 FF 0D 01 <LZ>` | `FUN_001143a8`/`FUN_0011706c` | difficulty / leading-zero target for next job |
| `0x0C` | `7F 55 FF 0C 39 …63B…` | `FUN_001143a8`/`FUN_0011706c` | **submit work** (40-byte header, §E.6) |

### C.2 ASIC → host replies (PROVEN by each handler in `FUN_001143a8 @ ~0x11805c`)

| RTYP | Query that elicits it | Handler computes | Corrected meaning |
|---|---|---|---|
| `0x80` | `7F 55 FF 80 06 00×6 59` | `noncecnt = b5+b6·256`; `pll = (b6'..b9')·10`; stores `pll` | **nonce-count + PLL status** (was mislabeled "chip ID") |
| `0x81` | `7F 55 FF 81 01 00 55` | two 12-bit fields → `tp0`,`tp1` via `41.74+(raw/4094-0.5)·220.5` | **die temperature**, two on-die sensors |
| `0x82` | `7F 55 FF 82 01 00 56` | copies bytes → `"model %02X: %s"` | **chip model/ID string** (was mislabeled "voltage") |
| `0x8E` | `7F 55 FF 8E 01 30 92` | `((raw·6-3)/16384-1)·0.2402` | **core voltage** (was mislabeled "status/nonce") |
| bit7=0 | — (unsolicited) | unpacks block/chip/core/nonce | **found-nonce result** (§D) |

Sensor constants are `.rodata` doubles: temp `0x118240=41.74`, `0x118238=220.5`,
`0x117ed0=1/4094`; volt `0x118230=0.2402`, `0x117ec8=1/16384`.

---

## D. The 8-byte read, corrected (PROVEN)

The 8-byte `read()` lives in `FUN_001176ec`, **not** in the nonce path. Sequence:

```
write(spi0_fd, {5E 58 55 52 59 56 53 57 54 51}, 10);   // fixed poll token
usleep(40);
read (spi0_fd, &buf, 8);                                // <-- the 8-byte read
```

`buf` is **4 × (status, data)** — one pair per board FIFO (KS0 populates one):

```
offset:  0     1     2     3     4     5     6     7
        st0   d0   st1   d1   st2   d2   st3   d3
```

For each pair, `status == 0x77 ('w')` means **that board's FIFO is empty**;
otherwise `data` is **one byte** of that board's ASIC serial stream, appended to
a per-board 2000-byte ring buffer. When a buffer overflows the code prints
`hash_boardN_err` and issues `FIFO RESET` (EMIO36 pulse).

So the eight bytes are a **FIFO drain**, carrying at most one ASIC-stream byte
per board per poll. They are **not** a nonce, status, ID, or any complete field.
The real ASIC frames (§B.2) are reassembled in software from the ring buffers by
`FUN_001143a8`, which hunts `0x55 0x7F`, collects 13 bytes, checks CHK, then
dispatches on `RTYP`.

**Found-nonce extraction (bit7=0 branch, PROVEN but nibble-packed):** from the
13-byte frame the code derives `block = b3>>4`, `chip = ((b2>>4)|((b3&0xF)<<4))-1`,
`core = b2&0xF`, and a 64-bit `nonce` assembled from `b4..b11` (little-endian,
with the two low bytes nibble-reordered against the metadata). It then prints
`block=%d, chip=%d, core=%d, nonce=%0llX, dup=%d` and the host re-runs the CPU
kHeavyHash (`FUN_001151a8`, `heavy_hash=`, `hash32=`) to validate before
submitting the share. The exact low-byte nibble order is reproduced in
`ks0_protocol/ks0proto.py::parse_rx_frame` and flagged there.

---

## E. ASIC lifecycle with byte-level evidence

1. **Power-up / PSU** (`FUN_00121ff4`): `pthread_mutex_init`; pulse EMIO16-19
   (`0x3D0-0x3D3`) low 500 ms then high; EMIO9 (`0x3C9`) low; raise EMIO28-31
   (`0x3DC-0x3DF`); `FIFO RESET` via EMIO36 (`0x3E4`); set PSU over i2c —
   `Set V 9512 %02x %02x`, `Set V bdp %02x %02x %02x %02x` (`FUN_001286ec/7b0`).
2. **SPI open / reset release** (`FUN_00116ca8`→`FUN_001169f4`): open
   `/dev/spidev0.0`, mode/bits/speed ioctls; `FUN_0011b59c` exports EMIO4-7, drives
   the reset/channel lines, `usleep`.
3. **Discovery + address assignment** (`FUN_0011b59c`): per channel (selected by
   EMIO5/6/7 via `FUN_0011b50c`) sweep `7F 55 00 02 01 <a>` for `<a>` = 1..0x12,
   4 channels → daisy-chain enumeration. `puts("config chip addr")`.
4. **Baud switch**: `7F 55 FF 0B 02 00 19` ("switch uart to 1M").
5. **Clock/PLL + timing**: `close core clock` `07 04 FF FF 00 00`; PLL
   `09 08 01 0B 00 00 00 07 D0 8A`; timing `05 03 C3 AC 3A`; then a walking-1s
   mask `07 04 00 01 FF FF` → … → `07 04 FF FF FF FF` (progressive core enable,
   15 ms between steps). Runtime per-chip PLL retune in `FUN_00116684`
   (`fall …`) / `FUN_001167fc` (`rise …`) using `0.16 PLL/MHz`.
6. **Work submission** (`FUN_001143a8`, twin `FUN_0011706c`): first
   `7F 55 FF 0D 01 <LZ>` (difficulty), then the 63-byte `0x0C` frame — LEN `0x39`,
   `prefix(2) | 14×00 | header40 reversed | job_id(0..0x7F) | CHK`. Only the
   **40-byte** header (`0x28`) is sent; the "same work" guard is `memcmp(...,0x28)`.
   **No M, v, or M×v bytes exist anywhere in the TX path.**
7. **Result retrieval**: poll loop (§D) → reassemble → bit7=0 nonce frames.
8. **Temp/status/errors**: periodic `0x80/0x82/0x81/0x8E` queries; watchdog pet
   `GPIO_DOG2 GPIO11` (EMIO11) every 60 s; `FIFO RESET` + `hash_boardN_err` on
   overflow; thermal PLL rise/fall.
9. **Shutdown/reset**: FIFO reset path, GPIO de-assert; firmware update path
   erases `/dev/mtd0/2` and re-flashes `BOOT.BIN`/rootfs (host-side only).

### GPIO (EMIO) map (PROVEN from `/sys/class/gpio` usage)

| EMIO (gpioN) | Used by | Function |
|---|---|---|
| 0-3 (`0x3C0-3C3`) | `FUN_00126cac` | board/PSU control |
| 2 (`0x3C2`) | `FUN_0011be0c` | (UART enable — dead path) |
| 4 (`0x3C4`) | `FUN_0011b59c` export, `FUN_001176ec` get | PL FIFO data-ready strobe |
| 5/6/7 (`0x3C5-3C7`) | `FUN_0011b50c`, `FUN_0011b59c` | **channel/board select** for the shared bus |
| 9 (`0x3C9`) | init | ASIC reset / enable gate |
| 11 (`0x3CB`) | `FUN_001143a8` | `GPIO_DOG2` watchdog pet |
| 16-19 (`0x3D0-3D3`) | init/power | per-board reset |
| 28-31 (`0x3DC-3DF`) | power | per-board power enable |
| 32-35 (`0x3E0-3E3`) | `FUN_001176ec` | per-board status flags |
| 36 (`0x3E4`) | `FUN_001176ec` | `FIFO RESET` strobe |

---

## F. Single-board-test call graph (PROVEN)

There is **no distinct ASIC test command or test binary**. The web/`bg` layer
(`appweb` + `controllers/user.c`) opens a TCP socket to the miner's control port
(`127.0.0.1:4111`, `send(sockfd, buf, ...)`) and forwards a **fixed JSON command
set**: `login, info, getnet, setnet, getlocate, setlocate, boardpow, state, fan,
getpool, setpool, board, getchipinfo, setchip, gethw, sethw, changepass, log,
restart, resetfactory, firmupdate, sync`. The string `"test failed"` in
`user.c` is only the generic fallback message for any reply with a non-zero
`code` and null `msg` — it is not an ASIC operation.

Therefore the repair-fixture "single-board test" is simply the **normal miner
init** (§E.1-5) running against one board: `bgserver.sh` launches
`iceriverminer -a kaspa -t 1 -o stratum+tcp://127.0.0.1:4869 …`; the board is
"tested" by whether chip enumeration (`0x02`), model read (`0x82`), temp
(`0x81`), voltage (`0x8E`) and found-nonce frames come back. The same ASIC call
graph (`FUN_0011b59c` → `FUN_001143a8`) is the only ASIC path that exists.
`--cputest` / `scanhash_kaspa_cpu` is a **CPU** algorithm self-check, not an ASIC
readout.

---

## G. Cross-model differences (PROVEN from the six binaries)

Opcode sets actually transmitted (from `analysis/commands/cmds_*.txt`):

| Model | TX opcodes | RX opcodes |
|---|---|---|
| KS0 | 01 02 05 07 09 0B 0C 0D | 80 81 82 8E |
| KS1, KS2 | 01 02 05 07 **08** 09 0B 0C 0D | 80 81 82 8E |
| KS3 | 01 02 05 **06** 07 08 09 0B 0C 0D | 80 81 8E |
| KS3L, KS3M | 01 02 05 **06** 08 09 0B 0C 0D (**no 07**) | 80 81 8E |

Differences and their proven/indicated nature:

* **`0x08`** (`7F 55 .. 08 01 01`, `7F 55 00 01 01 01`): per-chip reset/enable,
  present on all multi-chip models, absent on KS0 (KS0 uses only broadcast `0x01`).
  STRONGLY INDICATED (larger chip counts need per-chip addressing).
* **`0x06`** (`7F 55 FF 06 06 <6-byte mask>`): appears on KS3/KS3L/KS3M — a
  wider per-core/per-chip enable bitmap replacing the KS0 `0x07` nibble mask.
  STRONGLY INDICATED.
* **`0x07` dropped** on KS3L/KS3M; they enumerate with explicit per-chip
  `09 09 4D …` frames and `0C 01 1F` latches instead (visible in `cmds_KS3L.txt`).
* **`0x82` (model read) dropped** on KS3/KS3L/KS3M.
* The job `0x0C` frame and the `0x80/0x81/0x8E` sensor replies are **identical in
  structure** across all models.

These are **production feature differences** (more chips, more boards, different
enumeration), **not** debug commands. Opcode-number gaps are not treated as
evidence of hidden functionality.

---

## H. Remaining unexplained commands / registers / interfaces

* **Unused opcode space.** Writes `03 04 06(KS0) 08(KS0) 0A 0E 0F` and reads
  `83–8D 8F 90+` are **never sent or parsed** by the KS0 firmware. There is
  **zero** binary evidence assigning them any meaning. `ks0_protocol` can emit
  well-formed **read-class** frames (`build_unknown_read`) for `83–8D, 8F,
  90–97`, explicitly labeled UNKNOWN — these are for sacrificial-hardware probing
  only and are **not** proven to exist or to be harmless. SPECULATIVE.
* **No ASIC JTAG/BIST/scan-chain.** A string+code sweep of the whole KS0 firmware
  and OS found only (a) the Zynq **PS** boot JTAG in U-Boot (`jtagboot`,
  `JTAG Mode` in `BOOT2_0.BIN`) — controller-side, does not reach the hashing
  ASIC — and (b) generic `lspci`/`setpci` BIST strings. No ASIC-level debug
  vocabulary exists in firmware. (This does **not** prove the 1004LV100 silicon
  lacks an undocumented test mode — only that the firmware never uses one.)
* **`0x0B` 1 Mbaud frame** configures the ASIC's own serial side; the physical
  meaning of its `00 19` payload is unconfirmed. STRONGLY INDICATED = baud select.

---

## I. Strongest remaining route toward internal kHeavyHash state

**Digital readout: none (PROVEN negative within firmware).** The host sends only
the 40-byte header (`0x0C`) + difficulty (`0x0D`); the ASIC regenerates the
matrix `M`, the vector `v`, computes `M·v`, runs cSHAKE, and searches nonces
internally. The only ASIC→host data are: found nonces (bit7=0), nonce-count+PLL
(`0x80`), temperature (`0x81`), model (`0x82`), voltage (`0x8E`). **No command
requests `M`, `v`, `M·v`, pre-cSHAKE state, or internal registers**, and the
final hash passes through cSHAKE, which is not invertible to recover `M·v`.
The ASIC computing a value does not make it readable.

What **is** observable at the real interface, and usable as a black-box
primitive (SPECULATIVE, needs hardware):

1. **Determinism of the forward function.** `M` and `v` are deterministic public
   functions of the 40-byte header+seed; the host already has the full CPU
   reference (`scanhash_kaspa_cpu`, `singular::Svd<64,64>`, `Reflector<64>`). So
   `M·v` is computable off-ASIC for any chosen header — you do not need to read it
   out of the chip. The ASIC is only faster at the nonce search, not a source of
   otherwise-secret intermediates.
2. **Controlled-input response structure.** You fully control the 40-byte header,
   difficulty (`0x0D`), chip selection (EMIO5/6/7 channel mux + per-chip address),
   and PLL (`0x09`). Observable outputs per input: found-nonce rate/latency
   (`0x80` nonce-count), which cores report (`block/chip/core` fields),
   temperature and voltage reaction. These give **timing** and **error-rate**
   side channels as a function of the submitted work.
3. **Fault/marginal operation.** Pushing PLL (`0x09`) or voltage (i2c `Set V`)
   to the edge changes the error/duplicate-nonce behavior (`dup=%d`,
   `hash_boardN_err`). A differential fault-analysis style experiment on the
   nonce output under controlled marginal conditions is the only route that could
   expose anything about internal computation — and it yields statistics about the
   search, not a direct `M·v` tap.
4. **Passive capture first.** Before any write experiments, a logic analyzer on
   SPI0 (and the PL-FIFO strobe EMIO4) confirms this reconstruction against live
   traffic. Only then, and only on hardware you can destroy, try the UNKNOWN
   read-class frames from §H. **Do not send unknown write-class opcodes** — `0x09`
   adjoins PLL and the i2c path adjoins voltage; a malformed write can brick or
   over-volt a board. Even the read-class unknowns are not guaranteed harmless
   until verified on sacrificial hardware.

**Bottom line:** the corrected protocol provides **no digital path** to the
internal kHeavyHash matrix state. The matrix is recomputable off-chip from public
inputs, so the ASIC offers no secret there; the only chip-specific signals are
nonce-search timing/rate and thermal/voltage/error behavior under inputs you
control — a black-box timing/fault primitive, not a state readout.

---

### Reproduce

```
python3 ks0_protocol/ks0proto.py     # self-checks all templates + job frame
python3 ks0_protocol/examples.py     # byte-for-byte worked examples
```

Decompiles in `analysis/decompiled/*.c.gz` were produced with
`analysis/scripts/ghidra_dump_decompile.py` (Ghidra 11.2.1 headless); extract a
single function with `analysis/scripts/extract_function.py <FUN_addr>`.
