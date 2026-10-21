.section .boot, "ax"
.global _boot
_boot:
    auipc t0, 0x10000     # t0 = 0x20000000 + 0x10000000 = 0x30000000
    jr t0                 # 跳进 flash 的 _start
