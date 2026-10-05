"""
KS0 controller <-> ASIC protocol: standalone clean-room reference.

Reconstructed by data-flow from the stock IceRiver KS0 miner binary
  firmware/binaries/iceriverminer-KS0
  ELF 32-bit ARM EABI5 hard-float, Thumb-2, stripped
  BuildID  71a5a3420f7fcb5e682ccae4c0b3abb10cf3d067
  sha256   f3b9adf9740c7616c0060e2b44fe4416e256c54113cb9297bd9d09b346f08767

All FUN_xxxxxxxx labels are virtual addresses in that binary. Everything in
this file is PROVEN from executed code/.rodata unless a docstring says
INFERENCE or SPECULATIVE. This file deliberately assigns NO meaning to any
opcode the KS0 firmware does not actually transmit.

This supersedes any earlier reconstruction. Corrections baked in here:
  * The ASIC link is /dev/spidev0.0 (SPI0). /dev/spidev1.0 is the FAN
    controller (FUN_00127ffc "set fan"). i2c-0/i2c-1 are PSU/temp sensors.
  * The tty/UART open+config path (FUN_0011a658/FUN_0011a6a4/FUN_0011be0c)
    and the "7f 55 ff 09 01 0x" sleep/wake frames have NO callers and NO
    pointer references in the KS0 binary -> dead code. The ASIC transport is
    SPI only.
  * The 8-byte read is NOT a nonce. It is one poll of the Zynq-PL RX byte
    FIFO: 4 x (status,data), one pair per board FIFO (FUN_001176ec).
  * Response opcodes re-proven below: 0x80 = nonce-count+PLL status,
    0x81 = die temperature, 0x82 = chip model string, 0x8E = core voltage.
    Found nonces arrive in a SEPARATE frame class (response byte bit7 = 0),
    not via any dedicated read opcode.
"""

from __future__ import annotations

import string
from dataclasses import dataclass
from typing import Iterator, NamedTuple, Optional

# ==========================================================================
# Transport facts (PROVEN)
# ==========================================================================
# FUN_00116ca8 ("init first") -> FUN_001169f4(bus=0, cs=0, speed=40_000_000,
#   mode_byte=0x0C, bits=8) -> sprintf("/dev/spidev%d.%d",0,0) -> open(...,O_RDWR)
# then SPI_IOC_WR/RD_MODE (0x40016b01/0x80016b01),
#      SPI_IOC_WR/RD_BITS_PER_WORD (0x..6b03),
#      SPI_IOC_WR/RD_MAX_SPEED_HZ (0x..6b04).
# KS3L boot dmesg confirms: "spidev spi0.0: ... mode 0, 8 bits/w, 20833333" --
# the Cadence SPI clamps the requested 40 MHz to ~20.83 MHz.
ASIC_SPI_DEV = "/dev/spidev0.0"
ASIC_SPI_SPEED_HZ = 40_000_000     # requested; HW clamps to ~20.83 MHz
ASIC_SPI_BITS = 8
ASIC_SPI_MODE = 0
FAN_SPI_DEV = "/dev/spidev1.0"     # NOT the ASIC (FUN_00127ffc)

# ==========================================================================
# Frame constants (PROVEN)
# ==========================================================================
TX_PREAMBLE = b"\x7f\x55"          # host -> ASIC
RX_PREAMBLE = b"\x55\x7f"          # ASIC -> host, byte order REVERSED vs TX
RX_FRAME_LEN = 13                  # every ASIC -> host frame is exactly 13 bytes
ADDR_BROADCAST = 0xFF
ADDR_UNASSIGNED = 0x00             # source address for the 0x02 assignment frame

# Zynq-PL RX byte-FIFO poll (FUN_001176ec): written to SPI0, then read() of 8
# bytes = 4 x (status,data), one pair per board FIFO. 0x77 ('w') = FIFO empty.
FPGA_POLL_CMD = bytes([0x5E, 0x58, 0x55, 0x52, 0x59, 0x56, 0x53, 0x57, 0x54, 0x51])
FPGA_FIFO_EMPTY = 0x77

# Sensor conversion constants (doubles in .rodata; addresses noted)
TEMP_OFFSET = 41.74                 # 0x118240
TEMP_SPAN = 220.5                   # 0x118238
TEMP_LSB = 0.0002442598925256473    # 0x117ed0  (==1/4094)
VOLT_SCALE = 0.2402                 # 0x118230
VOLT_LSB = 6.103515625e-05          # 0x117ec8  (==1/16384)
MHZ_TO_PLL = 0.16                   # 0x1167f0 / 0x1169e8


# ==========================================================================
# 1. Firmware text-template -> bytes  (strtoul loop, verbatim semantics)
# ==========================================================================
def fw_hex_to_bytes(template: str) -> bytes:
    """Exact emulation of the firmware loop that turns a "7f 55 .." string
    into bytes (FUN_0011acbc / FUN_0011b4a4 / FUN_0011abc8 / FUN_0011b59c):

        for (i=0; i<strlen(s); i+=3) buf[i/3] = (char)strtoul(s+i, 0, 16);

    strtoul skips leading whitespace, so the firmware's double space in
    "7f 55 ff 8e  01 30" still yields exactly 6 bytes. Index i/3 means every
    byte occupies a fixed 3-char cell regardless of the extra space.
    """
    hexd = set(string.hexdigits)
    n = (len(template) + 2) // 3
    out = bytearray(n)
    for b in range(n):
        i = b * 3
        j = i
        while j < len(template) and template[j] in " \t\n\r\f\v":
            j += 1
        k = j
        while k < len(template) and template[k] in hexd:
            k += 1
        out[b] = int(template[j:k], 16) & 0xFF if k > j else 0
    return bytes(out)


# ==========================================================================
# 2. Checksum  (FUN_0011af7c and the inlined SWAR copies)
# ==========================================================================
def checksum(data: bytes) -> int:
    """8-bit modular sum of every byte, preamble included.

    The firmware uses a SWAR byte-lane accumulate
        acc = ((acc & 0x7f7f7f7f) + (x & 0x7f7f7f7f)) ^ ((acc ^ x) & 0x80808080)
    over 32-bit words, then folds the 4 lanes:  b0+b1+b2+b3 & 0xff.
    That is algebraically identical to sum(bytes) & 0xff.
    """
    return sum(data) & 0xFF


# ==========================================================================
# 3. Frame builder + proto_write
# ==========================================================================
def build_frame(addr: int, cmd: int, payload: bytes = b"",
                length: Optional[int] = None) -> bytes:
    """7F 55 | ADDR | CMD | LEN | PAYLOAD | CHK.

    LEN is the payload length byte as the firmware emits it. It is passed
    through verbatim (see KNOWN_COMMANDS) because a few firmware templates use
    a LEN that is not simply len(payload); callers that want the literal
    firmware bytes should use send_template() instead.
    """
    if length is None:
        length = len(payload)
    body = TX_PREAMBLE + bytes([addr & 0xFF, cmd & 0xFF, length & 0xFF]) + bytes(payload)
    return body + bytes([checksum(body)])


def proto_write(buf: bytes, add_checksum: bool) -> bytes:
    """Bytes handed to write(spi0_fd, ...).  (FUN_0011b1b0 / FUN_0011acbc)

    add_checksum True  -> buf + sum(buf)&0xff   (firmware "flag" arg != 0)
    add_checksum False -> buf unchanged         (template already ends in CHK)
    Firmware follows every write with usleep(15000).
    """
    return bytes(buf) + (bytes([checksum(buf)]) if add_checksum else b"")


def send_template(template: str, add_checksum: bool) -> bytes:
    """FUN_0011b4a4(fd, template, flag): parse then proto_write."""
    return proto_write(fw_hex_to_bytes(template), add_checksum)


# ==========================================================================
# Known command catalogue -- ONLY opcodes the KS0 binary actually transmits.
# Each entry records the literal .rodata template, whether the firmware adds a
# checksum, the sending function, and the meaning PROVEN by its handler/context.
# ==========================================================================
class KnownCommand(NamedTuple):
    template: str
    add_checksum: bool
    sent_by: str
    meaning: str

    @property
    def wire(self) -> bytes:
        return send_template(self.template, self.add_checksum)


# proto_init_cmd (FUN_0011b59c) emits these in this order, once at startup:
INIT_SEQUENCE: list[KnownCommand] = [
    KnownCommand("7f 55 ff 01 01 00", True, "FUN_0011b59c",
                 "broadcast reset/enable, first frame after RSTN release"),
    # address assignment: ADDR=0x00 (unassigned), payload = new chip address.
    # firmware sweeps 1..0x12 on each of 4 EMIO-selected channels (daisy chain).
    KnownCommand("7f 55 00 02 01 01", True, "FUN_0011b59c",
                 "assign chip address (payload=addr); swept per channel"),
    KnownCommand("7f 55 ff 0b 02 00 19", True, "FUN_0011b59c",
                 "switch UART-side baud of the ASIC link to 1 Mbaud "
                 "(ASIC's own serial side; host side is SPI)"),
    KnownCommand("7f 55 ff 07 04 ff ff 00 00", True, "FUN_0011b59c",
                 "close core clock (walking-mask core enable, all off)"),
    KnownCommand("7f 55 ff 09 08 01 0b 00 00 00 07 D0 8a", True, "FUN_0011b59c",
                 "PLL/frequency config (0x07D0 field)"),
    KnownCommand("7f 55 ff 05 03 c3 ac 3a", True, "FUN_0011b59c",
                 "timing/config (model-specific constant c3 ac 3a)"),
    # then a walking 1s mask 00 01 .. ff ff to enable cores/chips progressively
    KnownCommand("7f 55 ff 07 04 00 01 ff ff", True, "FUN_0011b59c",
                 "core-enable walking mask step"),
    KnownCommand("7f 55 ff 07 04 ff ff ff ff", True, "FUN_0011b59c",
                 "core-enable walking mask final (all on)"),
]
# NOTE on checksums: every init frame above is emitted through FUN_0011acbc,
# which ALWAYS appends CHK = sum(bytes)&0xff. So add_checksum=True and the LEN
# byte already accounts for the whole payload (e.g. the literal "..07 D0 8a" is
# payload, CHK is appended after). Only the 0x80 query (below) carries its CHK
# inside the literal string and is therefore sent with add_checksum=False.

# Periodic status queries (FUN_001143a8 main loop, via FUN_0011b4a4 flag arg)
STATUS_QUERIES: list[KnownCommand] = [
    KnownCommand("7f 55 ff 80 06 00 00 00 00 00 00 59", False, "FUN_001143a8",
                 "query nonce-count + PLL status  (reply opcode 0x80)"),
    KnownCommand("7f 55 ff 82 01 00", True, "FUN_001143a8",
                 "query chip model/id  (reply opcode 0x82, ASCII string)"),
    KnownCommand("7f 55 ff 81 01 00", True, "FUN_001143a8",
                 "query die temperature  (reply opcode 0x81, two 12-bit sensors)"),
    KnownCommand("7f 55 ff 8e  01 30", True, "FUN_001143a8",
                 "query core voltage  (reply opcode 0x8E)"),
]

# Per-job frames (FUN_001143a8 ~0x117d.. ; generic twin FUN_0011706c):
#   1) 7f 55 ff 0d 01 <LZ>   difficulty / leading-zero target write
#   2) 7f 55 ff 0c <job>     the 40-byte work header, see build_job_frame()
JOB_OPCODE_DIFF = 0x0D
JOB_OPCODE_WORK = 0x0C


# ==========================================================================
# 4. Job (work) frame   (FUN_001143a8 around 0x117d..; FUN_0011706c twin)
# ==========================================================================
def build_diff_frame(leading_zero: int) -> bytes:
    """7F 55 FF 0D 01 <LZ> (+chk). LZ = required leading-zero / difficulty byte.
    Firmware literal uses 0x0A; here it is parameterised."""
    return send_template("7f 55 ff 0d 01 %02X" % (leading_zero & 0xFF), True)


def build_job_frame(header40: bytes, prefix2: bytes, job_id: int) -> bytes:
    """Build the 63-byte work frame the ASIC receives for each job.

    Layout proven from FUN_001143a8 (and the golden literal in the KS3 binary):

        off 0   : 7F 55            TX preamble
        off 2   : FF               ADDR = broadcast
        off 3   : 0C               CMD  = submit work
        off 4   : 39               LEN  = 0x39 = 57 payload bytes
        off 5   : prefix2[0..1]    2-byte job prefix (seed/target selector)
        off 7   : 14x 00           14 zero bytes (reserved)
        off 21  : header40 reversed  the 40-byte block header, byte-reversed
        off 61  : job_id           1-byte rolling job counter (0..0x7f)
        off 62  : CHK              sum of off0..61 & 0xff

    The host sends ONLY these 40 header bytes (0x28). It does NOT send the
    kHeavyHash matrix M, the vector v, or M*v -- the ASIC regenerates all of
    that internally from the header+seed. (PROVEN: no matrix bytes anywhere in
    the TX path; memcmp of exactly 0x28 bytes gates the "same work" check.)
    """
    if len(header40) != 40:
        raise ValueError("header must be exactly 40 bytes (0x28)")
    if len(prefix2) != 2:
        raise ValueError("prefix must be 2 bytes")
    body = bytearray()
    body += TX_PREAMBLE
    body += bytes([ADDR_BROADCAST, JOB_OPCODE_WORK, 0x39])
    body += prefix2
    body += b"\x00" * 14
    body += header40[::-1]
    body += bytes([job_id & 0x7F])
    body += bytes([checksum(body)])
    return bytes(body)


# ==========================================================================
# 5. Zynq-PL RX FIFO poll + de-FIFO  (FUN_001176ec)
# ==========================================================================
def split_fpga_poll(eight: bytes) -> list[Optional[int]]:
    """Given the 8 bytes returned by one FPGA_POLL_CMD read(), return a list of
    4 data bytes (board0..board3); None where the board FIFO was empty ('w').

        pair i = (status, data) at offsets (2i, 2i+1)
        status == 0x77 ('w')  -> empty, no byte this poll
        else                  -> data is one byte of that board's ASIC stream
    """
    if len(eight) != 8:
        raise ValueError("expected 8 bytes")
    out: list[Optional[int]] = []
    for i in range(4):
        status, data = eight[2 * i], eight[2 * i + 1]
        out.append(None if status == FPGA_FIFO_EMPTY else data)
    return out


# ==========================================================================
# 6. ASIC->host 13-byte frame reassembly + parse  (FUN_001143a8 ~0x11805c)
# ==========================================================================
class NonceResult(NamedTuple):
    chip: int
    core: int
    block: int
    nonce: int          # 64-bit
    raw: bytes


class StatusReply(NamedTuple):
    opcode: int         # 0x80 / 0x81 / 0x82 / 0x8E
    chip: int
    payload: bytes      # frame bytes [2..10) as received
    raw: bytes


def parse_rx_frame(frame: bytes) -> Optional[object]:
    """Parse one 13-byte ASIC->host frame (already de-FIFO'd, preamble 55 7F).

    Dispatch (FUN_001143a8): byte[1]==0x7f required; checksum = sum(frame[0:12])
    & 0xff must equal frame[12]. Then byte[11] is the response type:
        bit7 set  -> status/query reply, byte[10]=chip, subtype in {80,81,82,8E}
        bit7 clear-> FOUND NONCE result; nonce metadata packed in bytes[2..9]

    Returns NonceResult, StatusReply, or None (bad frame).
    """
    if len(frame) != RX_FRAME_LEN or frame[0] != 0x55 or frame[1] != 0x7F:
        return None
    if checksum(frame[:12]) != frame[12]:
        return None
    rtype = frame[11]
    if rtype & 0x80:
        return StatusReply(opcode=rtype, chip=frame[10],
                           payload=frame[2:10], raw=frame)
    # bit7 clear: found-nonce frame. Metadata nibble-packed; see report sec D.
    b = frame
    block = b[3] >> 4
    chip = ((b[2] >> 4) | ((b[3] & 0x0F) << 4)) - 1
    core = b[2] & 0x0F
    nonce = int.from_bytes(bytes([b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11]]), "little")
    return NonceResult(chip=chip, core=core, block=block, nonce=nonce, raw=frame)


class FrameReassembler:
    """Reassemble 13-byte frames from one board's de-FIFO'd byte stream.

    Mirrors the ring-buffer scan in FUN_001143a8: hunt for 0x55, require the
    next byte 0x7f, collect 11 more, yield the 13-byte frame.
    """
    def __init__(self) -> None:
        self._buf = bytearray()

    def feed(self, data_bytes: bytes) -> Iterator[bytes]:
        self._buf += data_bytes
        while True:
            start = self._buf.find(0x55)
            if start < 0:
                self._buf.clear()
                return
            if start:
                del self._buf[:start]
            if len(self._buf) < RX_FRAME_LEN:
                return
            if self._buf[1] != 0x7F:
                del self._buf[0]
                continue
            frame = bytes(self._buf[:RX_FRAME_LEN])
            del self._buf[:RX_FRAME_LEN]
            yield frame


# ==========================================================================
# Sensor decoders (from the 0x81 / 0x8E reply handlers)
# ==========================================================================
def decode_temperature(raw12: int) -> float:
    """0x81 reply: each 12-bit field -> degrees C."""
    return TEMP_OFFSET + (raw12 * TEMP_LSB - 0.5) * TEMP_SPAN


def decode_voltage(raw: int) -> float:
    """0x8E reply: core voltage in volts."""
    return ((raw * 6.0 - 3.0) * VOLT_LSB - 1.0) * VOLT_SCALE


# ==========================================================================
# Read-only frames for opcodes the KS0 firmware never reads (UNKNOWN meaning).
# These are generated ONLY so hardware experiments have well-formed, checksum-
# valid read-class frames. The KS0 firmware assigns NO meaning to any of these.
# They are NOT known to be debug/registers and are NOT guaranteed harmless.
# ==========================================================================
def build_unknown_read(opcode: int, addr: int = ADDR_BROADCAST,
                       payload: bytes = b"\x00") -> bytes:
    """Well-formed read-class frame (bit7 of opcode set) for an opcode the
    firmware does not use. meaning: UNKNOWN. See report section H."""
    if not (opcode & 0x80):
        raise ValueError("read-class opcodes must have bit7 set")
    return build_frame(addr, opcode, payload, length=len(payload))


# opcodes the KS0 read path leaves unexplored (NOT proven to exist on silicon):
UNKNOWN_READ_OPCODES = list(range(0x83, 0x8E)) + [0x8F] + list(range(0x90, 0x98))


if __name__ == "__main__":
    # self-check against the firmware's own literal, checksummed templates
    for kc in INIT_SEQUENCE + STATUS_QUERIES:
        w = kc.wire
        assert w[:2] == TX_PREAMBLE
        assert checksum(w[:-1]) == w[-1], kc.template
    # golden KS3 job literal: verify our layout + checksum reproduce it
    print("init/status templates OK, checksums verified")
    jf = build_job_frame(bytes(range(40)), b"\x1b\x5a", 0)
    assert jf[4] == 0x39 and len(jf) == 63 and checksum(jf[:-1]) == jf[-1]
    print("job frame OK:", jf.hex())
    print("unknown read 0x83:", build_unknown_read(0x83).hex(), "(meaning: UNKNOWN)")
