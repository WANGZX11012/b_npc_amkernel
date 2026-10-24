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

VERILATOR_FLAGS = --cc --exe --build  --Mdir $(BUILD_DIR) \
                  -I$(abspath vsrc) \
                  -CFLAGS "-DTRACE_ENABLE=$(TRACE_ENABLE) -I$(NPC_CSRC) -I$(NEMU_INC) -DENABLE_DIFFTEST=$(ENABLE_DIFFTEST)" \
                  -LDFLAGS "-ldl" \
                  -Wall -Wno-fatal \
                  --top-module $(TOPNAME) \
                  -MAKEFLAGS "OPT_FAST=-O3 OPT_GLOBAL=-O3"

# ── Kconfig ──
include $(NPC_HOME)/scripts/config.mk
-include $(NPC_HOME)/include/config/auto.conf
# 必须在 include auto.conf 之后才能读 CONFIG_WAVE
TRACE_ENABLE := $(if $(CONFIG_WAVE),1,0)
VERILATOR_FLAGS += $(if $(CONFIG_WAVE),--trace)


# 必须在 include auto.conf 之后，否则 CONFIG_xxx 未定义
VERILATOR_FLAGS += $(if $(CONFIG_HAS_LFSR),+define+HAS_LFSR)
VERILATOR_FLAGS += $(if $(CONFIG_DATA_MEM_DELAY),+define+DATA_MEM_DELAY=$(CONFIG_DATA_MEM_DELAY))
VERILATOR_FLAGS += $(if $(CONFIG_DPI_MEM),+define+DPI_MEM)
VERILATOR_FLAGS += $(if $(CONFIG_PERF),+define+PERF_ENABLE)
# ── 统计打印开关 (menuconfig) ──
VERILATOR_FLAGS += $(if $(CONFIG_PRINT_ICACHE),+define+PRINT_ICACHE)
#icache 参数设置 块数量
VERILATOR_FLAGS += $(if $(CONFIG_ICACHE_INDEX_BITS),+define+ICACHE_INDEX_BITS=$(CONFIG_ICACHE_INDEX_BITS))
#icache 参数设置 一个块多大
VERILATOR_FLAGS += $(if $(CONFIG_ICACHE_BLOCK_BYTES),+define+ICACHE_BLOCK_BYTES=$(CONFIG_ICACHE_BLOCK_BYTES))

# ── ITRACE (menuconfig): 传给 C++ 侧 ──
ITRACE_ENABLE := $(if $(CONFIG_ITRACE),1,0)
VERILATOR_FLAGS += -CFLAGS "-DITRACE_ENABLE=$(ITRACE_ENABLE)"
# CACHESIM 由 menuconfig 控制：跑完自动跑一次 cachesim
CACHESIM := $(if $(CONFIG_CACHESIM),1,0)





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
# 	这个之后生成的itrace.bin 只要开了itrace
ifeq ($(CACHESIM),1)
	@$(MAKE) -s -C cachesim
	@./cachesim/cachesim $(BUILD_DIR)/itrace.bin
endif



wave:
	@gtkwave $(BUILD_DIR)/sim.vcd &

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./perf.csv



# ══════════════════════════════════════════════════════════════
#  make perf —— 一键复现性能数据 (讲义「记录性能数据」要求)
#
#  用法:
#    make perf                 # 默认 test 规模, 快 (约 500K 指令)
#    make perf PERF_SIZE=train # 正式记录规模 (约 60M 指令)
# ══════════════════════════════════════════════════════════════
PERF_SIZE ?= test
AM_HOME   ?= ../abstract-machine
BENCH_DIR ?= ../am-kernels/benchmarks/microbench
BENCH_BIN ?= $(BENCH_DIR)/build/microbench-riscv32-npc.bin
PERF_BIN  := $(BUILD_DIR)/perf.bin
PERF_LOG  := $(BUILD_DIR)/perf.log
PERF_CSV  := perf.csv

perf: all
	@mkdir -p $(BUILD_DIR)
	@echo "[perf] 重建基准 (mainargs=$(PERF_SIZE))..."
	@rm -f $(BENCH_BIN)
	@$(MAKE) -s -C $(BENCH_DIR) ARCH=riscv32-npc mainargs=$(PERF_SIZE) insert-arg
	@cp $(BENCH_BIN) $(PERF_BIN)
	@./$(BUILD_DIR)/V$(TOPNAME) -b $(PERF_BIN) 2>&1 | tee $(PERF_LOG)
	@echo ""
	@test -f $(PERF_CSV) || echo "commit,insts,cycles,cpi,ipc,ifu_ev,ifu_pct,lsu_ev,mem_pct,alu,load,store" > $(PERF_CSV)
	@python3 scripts/perf_report.py $(PERF_LOG) --csv >> $(PERF_CSV)
	@python3 scripts/perf_report.py $(PERF_LOG)
	@tail -1 $(PERF_CSV)

