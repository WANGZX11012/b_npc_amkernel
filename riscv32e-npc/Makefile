TOPNAME = top
VERILATOR = verilator

VSRCS = $(wildcard vsrc/*.v)  #把 vsrc/ 目录下所有 .v 文件都收集到 VSRCS 变量里。
CSRCS = $(wildcard csrc/*.cpp)


VHSRCS = $(wildcard vsrc/*.vh)  #把 vsrc/ 目录下所有 .vh 文件都收集到 VSRCS 变量里。

OBJ_DIR = obj_dir
BIN = $(OBJ_DIR)/V$(TOPNAME)
WAVE = $(OBJ_DIR)/wave.vcd
REF_SO = $(OBJ_DIR)/ref.so
NPC_VSRCS_INC = $(abspath ./vsrc)
AM_HOME = $(abspath ../abstract-machine)
AM_INC = $(AM_HOME)/am/include
KLIB_INC = $(AM_HOME)/klib/include

VERILATOR_FLAGS = --cc --exe -I$(NPC_VSRCS_INC) --build --trace -Wall -Wno-fatal --top-module $(TOPNAME)
NPC_NEMU_INC = $(abspath ./npc-nemu/include)
NPC_CSRCS_INC = $(abspath ./csrc)


# ── 从 npc-nemu 的 Kconfig 产物读取 DIFFTEST 开关 ──
NPC_AUTO_CONF :=$(abspath ./npc-nemu/include/config/auto.conf) 
-include $(NPC_AUTO_CONF)

ifeq ($(CONFIG_HAS_SERIAL),y)
CSRCS += csrc/device/serial.cpp
endif
ifeq ($(CONFIG_HAS_TIMER),y)
CSRCS += csrc/device/timer.cpp
endif
ifeq ($(CONFIG_HAS_VGA),y)
CSRCS += csrc/device/vga.cpp
endif
ifeq ($(CONFIG_HAS_KEYBOARD),y)
CSRCS += csrc/device/keyboard.cpp
endif

ifeq ($(CONFIG_DIFFTEST),y)
ENABLE_DIFFTEST :=1
else
ENABLE_DIFFTEST :=0
endif

ifeq ($(CONFIG_USE_SRAM),y)
VERILATOR_FLAGS += +define+USE_SRAM
endif

# Pass include paths and feature macros to verilator's -CFLAGS
VERILATOR_FLAGS += -CFLAGS "-I$(NPC_NEMU_INC) -I$(NPC_CSRCS_INC) -I$(AM_INC) -I$(KLIB_INC) -DENABLE_DIFFTEST=$(ENABLE_DIFFTEST)" 
ifeq ($(CONFIG_HAS_VGA),y)
VERILATOR_FLAGS += -LDFLAGS "-lSDL2"
endif

# ═══════════════════════════════════════════════════════════
# 统一构建nemu和npc
# ═══════════════════════════════════════════════════════════
all:build

build: build-verilog build-nemu


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 优化：只在目标不存在或源更新时才重新链接
$(REF_SO): $(abspath ../nemu/build/riscv32-nemu-interpreter-so) | $(OBJ_DIR)
	ln -sf $< $@

#auto.conf 变了就强制 Verilator 重跑
build-verilog: $(NPC_AUTO_CONF)
	$(VERILATOR) $(VERILATOR_FLAGS) $(VSRCS) $(CSRCS) $(VHSRCS)

build-nemu:
	$(MAKE) -C npc-nemu all; 

run: build
	 $(MAKE) -C npc-nemu run IMG=$(IMG)

#DO NOT REMOVE THIS LINE!!!
sim: build
	$(call git_commit, "sim RTL") 
	@echo "Write this Makefile by your self."
	$(BIN)
	gtkwave $(WAVE)

clean:
	rm -rf $(OBJ_DIR)
	rm -f ./hex/*.log
	$(MAKE) -C npc-nemu clean

FORCE:

.PHONY: all build build-verilog build-nemu run sim clean FORCE

include ../Makefile
