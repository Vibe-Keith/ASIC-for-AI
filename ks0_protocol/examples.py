"""
Worked, byte-for-byte examples validated against literals in the stock binaries.

Run:  python3 examples.py
"""
from ks0proto import (
    fw_hex_to_bytes, checksum, send_template, build_job_frame,
    split_fpga_poll, parse_rx_frame, FrameReassembler, NonceResult, StatusReply,
    decode_temperature, decode_voltage, build_unknown_read,
    INIT_SEQUENCE, STATUS_QUERIES, UNKNOWN_READ_OPCODES,
)


def h(b: bytes) -> str:
    return " ".join("%02X" % x for x in b)


def demo_known_commands() -> None:
    print("== KNOWN host->ASIC frames (exact wire bytes) ==")
    for kc in INIT_SEQUENCE + STATUS_QUERIES:
        print("  %-46s  %s" % (h(kc.wire), kc.meaning))


def demo_golden_job() -> None:
    # Golden 0x0C work frame literal embedded in the KS3 binary (-KS3), used
    # here only to prove build_job_frame() reproduces the real layout + CHK.
    golden = fw_hex_to_bytes(
        "7f 55 FF 0c 39 1b 5a 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
        "01 81 2e 88 54 c2 f2 11 5d 52 ad 94 6a 84 ac 78 5a 1b 1e b7 46 4d 88 "
        "a4 ba e7 14 89 ae 18 e6 04 5b f5 be 32 11 76 00")
    golden = golden + bytes([checksum(golden)])  # firmware appends CHK (flag=1)
    prefix = golden[5:7]
    header_rev = golden[21:61]
    header40 = header_rev[::-1]
    job_id = golden[61]
    rebuilt = build_job_frame(header40, prefix, job_id)
    print("\n== GOLDEN 0x0C work frame ==")
    print("  literal :", h(golden))
    print("  rebuilt :", h(rebuilt))
    print("  match   :", rebuilt == golden)
    print("  LEN=0x%02X payload=%d, header is 40B (0x28) sent byte-reversed"
          % (golden[4], golden[4]))


def demo_fpga_poll() -> None:
    print("\n== 8-byte FPGA RX-FIFO poll (NOT a nonce) ==")
    # 4 x (status,data): board0 empty, board1 gave 0x55, board2 empty, board3 0x7f
    eight = bytes([0x77, 0x00, 0x00, 0x55, 0x77, 0x00, 0x00, 0x7F])
    print("  poll cmd   :", h(fw_hex_to_bytes("5e 58 55 52 59 56 53 57 54 51")))
    print("  read(8)    :", h(eight))
    print("  de-FIFO'd  :", split_fpga_poll(eight),
          "(None = that board FIFO empty)")


def demo_rx_parse() -> None:
    print("\n== ASIC->host 13-byte frames ==")
    # Build a well-formed 0x81 temperature reply (bit7 set) for chip 0x03
    body = bytearray([0x55, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x03, 0x81])
    body.append(checksum(body))
    r = parse_rx_frame(bytes(body))
    print("  0x81 reply :", h(body), "->", r)
    # A found-nonce frame (bit7 clear). Metadata nibble-packed per report sec D.
    nf = bytearray([0x55, 0x7F, 0x11, 0x10, 0xDE, 0xAD, 0xBE, 0xEF,
                    0x01, 0x02, 0x03, 0x00])
    nf.append(checksum(nf))
    print("  nonce frame:", h(nf), "->", parse_rx_frame(bytes(nf)))
    # reassembly from a noisy byte stream (how FUN_001143a8 actually works)
    ra = FrameReassembler()
    stream = b"\x99\x99" + bytes(body) + b"\xAA" + bytes(nf)
    got = list(ra.feed(stream))
    print("  reassembled %d frame(s) from noisy stream" % len(got))


def demo_sensors() -> None:
    print("\n== sensor decode ==")
    print("  temp raw 0x7FF -> %.2f C" % decode_temperature(0x7FF))
    print("  volt raw 0x555 -> %.4f V" % decode_voltage(0x555))


def demo_unknown_reads() -> None:
    print("\n== read-class frames for UNUSED opcodes (meaning: UNKNOWN) ==")
    print("  The KS0 firmware never sends or parses these. They are well-formed")
    print("  read-class frames ONLY. NOT proven to exist on silicon, NOT proven")
    print("  harmless. For sacrificial-hardware experiments only.")
    for op in UNKNOWN_READ_OPCODES:
        print("  op 0x%02X -> %s" % (op, h(build_unknown_read(op))))


if __name__ == "__main__":
    demo_known_commands()
    demo_golden_job()
    demo_fpga_poll()
    demo_rx_parse()
    demo_sensors()
    demo_unknown_reads()
