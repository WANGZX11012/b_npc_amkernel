.DEFAULT_GOAL := all

TOPNAME   = top
BUILD_DIR = build
NPC_HOME  = $(abspath .)
NPC_CSRC  = $(NPC_HOME)/csrc

VSRCS  = $(sort $(wildcard vsrc/*.v))
VHSRCS = $(wildcard vsrc/*.vh)
CSRCS  = $(NPC_CSRC)/main.c          \
         $(NPC_CSRC)/npc.cpp         \
         $(NPC_CSRC)/difftest.cpp    \
         $(NPC_CSRC)/dpic_mem.cpp    \
         $(NPC_CSRC)/monitor/monitor.c \
         $(NPC_CSRC)/cpu/cpu-exec.c  \
         $(NPC_CSRC)/sdb/sdb.c

# NEMU 的 include(提供 difftest-def.h)和 ref.so
NEMU_INC  = $(abspath ../nemu/include)
REF_SO    = $(abspath ../nemu/build/riscv32-nemu-interpreter-so)

VERILATOR_FLAGS = --cc --exe --build --trace --Mdir $(BUILD_DIR) \
                  -I$(abspath vsrc) \
                  -CFLAGS "-I$(NPC_CSRC) -I$(NEMU_INC) -DENABLE_DIFFTEST=$(ENABLE_DIFFTEST)" \
                  -LDFLAGS "-ldl" \
                  -Wall -Wno-fatal \
                  --top-module $(TOPNAME)

# ── Kconfig ──
include $(NPC_HOME)/scripts/config.mk
-include $(NPC_HOME)/include/config/auto.conf

# 必须在 include auto.conf 之后，否则 CONFIG_xxx 未定义
VERILATOR_FLAGS += $(if $(CONFIG_HAS_LFSR),+define+HAS_LFSR)
VERILATOR_FLAGS += $(if $(CONFIG_DATA_MEM_DELAY),+define+DATA_MEM_DELAY=$(CONFIG_DATA_MEM_DELAY))
VERILATOR_FLAGS += $(if $(CONFIG_DPI_MEM),+define+DPI_MEM)

# DPI_MEM 的内存由 C++ 侧 dpi_pmem_words[] 自己持有 (见 csrc/dpic_mem.cpp),
# 不依赖 NEMU pmem, 因此 DPI_MEM 与 DIFFTEST 解耦, 二者可独立开关。
# 若同时开 DIFFTEST, 由 difftest.cpp 用 dpi_pmem_copy_out() 把 DUT 内存同步给 REF。

# WAVE 由 menuconfig 控制：CONFIG_WAVE=y → make run 自动带 -w
ifeq ($(CONFIG_WAVE),y)
RUN_FLAGS += -w
endif

# BATCH 由 menuconfig 控制：CONFIG_BATCH=y → make run 自动带 -b（批处理跑完）
ifeq ($(CONFIG_BATCH),y)
RUN_FLAGS += -b
endif

# DIFFTEST 由 menuconfig 控制：CONFIG_DIFFTEST=y → 编译 difftest 并拷贝 ref.so
ifeq ($(CONFIG_DIFFTEST),y)
ENABLE_DIFFTEST :=1
else
ENABLE_DIFFTEST :=0
endif

# bin2readmemh.py: 把 AM 编出的 .bin 转成 Verilog $readmemh 兼容的 hex 格式
BIN2HEX := $(NPC_HOME)/../abstract-machine/tools/bin2readmemh.py
# inst_mem.v 中 $readmemh("build/img.hex") 的加载目标（相对运行目录 npc/）
IMG_HEX := $(BUILD_DIR)/img.hex

.PHONY: all run wave clean

all:
	@verilator $(VERILATOR_FLAGS) $(VSRCS) $(CSRCS)
ifeq ($(CONFIG_DIFFTEST),y)
	@cp $(REF_SO) $(BUILD_DIR)/ref.so
endif

run: all
# 仅当命令行传入的IMG非空 ifneq是判断是不是空的 IMG=xxx.bin 时才转换镜像，否则跑 inst_mem 内置的 4 条占位指令
ifneq ($(IMG),)
	@python3 $(BIN2HEX) $(IMG) $(IMG_HEX)   # .bin -> build/img.hex
	@echo "[npc] load $(IMG) -> $(IMG_HEX)"  # 打印加载路径供确认
endif
	@./$(BUILD_DIR)/V$(TOPNAME)  $(RUN_FLAGS) $(IMG)

wave:
	@gtkwave $(BUILD_DIR)/sim.vcd &

clean:
	rm -rf $(BUILD_DIR)
