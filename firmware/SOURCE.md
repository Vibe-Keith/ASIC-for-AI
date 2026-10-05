# Firmware provenance

All firmware here was published by the Kaspa mining community, not extracted by
this project. Vendored subset only — see "What is / isn't here" below.

## Origin

* Repository: `github.com/mcmickburns/iceriverminer_dump` (public), which in turn
  mirrors stock firmware from `iceriver.io/firmware-download/`.
* Firmware package: `ICERIVER-KAS-KS0-20230916` (and the KS1/KS2/KS3/KS3L/KS3M
  packages of the same date) and a KS3L OS rootfs dump.
* The stock `.bgz` images are encrypted with the vendor `jm` tool; the upstream
  repo contains the decrypted/extracted `extract/` trees used here.

## Vendored binaries (stock, unmodified)

sha256:

```
f3b9adf9740c7616c0060e2b44fe4416e256c54113cb9297bd9d09b346f08767  binaries/iceriverminer-KS0
73b5474f457dbece418e9ef7ab997bc104a1348dc8b16da2a073ca088cff1fee  binaries/iceriverminer-KS1
f431e857b7963462d596a65582873f62dd097f35cfa9918101fa7cfd522ab156  binaries/iceriverminer-KS2
0d5e118c9323d5765f92422a943947b939b886d20749c000baec9e7ee4799320  binaries/iceriverminer-KS3
b90d9ecb9f59527ec4088b2adef0b24c87f3365d4814d1a6df5c089fb20e1695  binaries/iceriverminer-KS3L
a1f19b7cd1f72ffc3e5ac7236988063d374101113698d241f5f0700bdf498dcc  binaries/iceriverminer-KS3M
```

All six: ELF 32-bit LSB ARM EABI5 hard-float, dynamically linked, stripped.
KS0 BuildID `71a5a3420f7fcb5e682ccae4c0b3abb10cf3d067`.

## What is / isn't here

**Included** (the forensically relevant subset, ~9 MB):
* `binaries/` — the six stock `iceriverminer` ELF binaries.
* `KS0_bg/` — the KS0 web/control-plane source `controllers/user.c`, `utils.h`
  and appweb config (shows the TCP:4111 JSON command set; see report §F).
* `OS/bgserver.sh` — the init.d startup (how the miner is launched).
* `OS/dmesg-KS3L.txt` — boot log proving the Zynq-7000 SoC, `spidev spi0.0/spi1.0`
  modes/speeds, and the UART/I2C/watchdog/FPGA-manager topology (report §A).

**Not included** (large, redundant, or not needed to reproduce the analysis):
* The full 1.1 GB upstream clone (includes 187 MB of git history, the 343 MB KS3L
  OS rootfs with python2.7, and overclock firmware variants).
* The `bg` appweb runtime binaries (~25 MB of precompiled server).
* Encrypted `.bgz` originals.

To obtain the full dump: `git clone https://github.com/mcmickburns/iceriverminer_dump`.

## Legal / ethics

These are redistributable community-published firmware images analyzed for
interoperability and security research (understanding the controller↔ASIC
protocol of hardware one owns). No vendor code is modified here.
