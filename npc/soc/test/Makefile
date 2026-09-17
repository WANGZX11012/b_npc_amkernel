# ══════════════════════════════════════════════════════════════
#  npc/soc/test/Makefile — 把 C 测试程序编成 MROM 能吃的 .bin
#
#  soc_tb.cpp 的工作目录是 npc/soc/, 所以产物放这里,
#  tb 里写 "test/xxx.bin" 就能找到。
# ══════════════════════════════════════════════════════════════

# 1. 工具链前缀 —— 和 AM 的 isa/riscv.mk 保持一致
CROSS  = riscv64-linux-gnu-

# 2. 编译选项
#    -nostdlib -nostartfiles -ffreestanding : 没有 libc / CRT, _start 就是全部
#    -march/-mabi                            : 和 riscv32-npc.mk 一致(你的 CPU 是 rv32i)
#    -O2 -fomit-frame-pointer                : 尽量不用栈(复位后 sp=0, 一碰栈就访问地址 0)
CFLAGS = -march=rv32i_zicsr -mabi=ilp32 \
         -nostdlib -nostartfiles -ffreestanding \
         -O2 -fomit-frame-pointer

# 3. 代码链接到哪 —— MROM 基址
#    做成变量: 以后想链接到别的地址(比如 SRAM)只改这一处
TEXT_ADDR ?= 0x20000000

# 4. .elf 是中间产物, 但我们还要留着 objdump 检查,
#    不声明的话 make 会把它当"中间文件"删掉
.PRECIOUS: %.elf

# 5. 默认目标: 把当前目录所有 .c 都编成 .bin
SRCS = $(wildcard *.c)
BINS = $(SRCS:.c=.bin)

.PHONY: all clean
all: $(BINS)

# 6. 规则一: .c → .elf       $< = 依赖 = xxx.c    $@ = 目标 = xxx.elf
%.elf: %.c
	$(CROSS)gcc $(CFLAGS) -Wl,-Ttext=$(TEXT_ADDR) -e _start -o $@ $<

# 7. 规则二: .elf → .bin     只抽 .text !
%.bin: %.elf
	$(CROSS)objcopy -O binary --only-section=.text $< $@

clean:
	rm -f *.elf *.bin
