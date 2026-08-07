AM_SRCS := riscv/npc/start.S \
           riscv/npc/trm.c \
           riscv/npc/ioe.c \
           riscv/npc/timer.c \
           riscv/npc/input.c \
           riscv/npc/gpu.c \
           riscv/npc/cte.c \
           riscv/npc/trap.S \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDSCRIPTS += $(AM_HOME)/scripts/linker.ld
LDFLAGS   += --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start

MAINARGS_MAX_LEN = 64
MAINARGS_PLACEHOLDER = the_insert-arg_rule_in_Makefile_will_insert_mainargs_here
CFLAGS += -DMAINARGS_MAX_LEN=$(MAINARGS_MAX_LEN) -DMAINARGS_PLACEHOLDER=$(MAINARGS_PLACEHOLDER)

insert-arg: image
	@python $(AM_HOME)/tools/insert-arg.py $(IMAGE).bin $(MAINARGS_MAX_LEN) $(MAINARGS_PLACEHOLDER) "$(mainargs)"

image: image-dep
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

# NPC_RUN_MODE: dpi=单周期(DPI-C喂指令)  sram=多周期(Verilog内部SRAM,$readmemh加载)
# 默认 dpi，由各 arch mk 在 include 前覆盖
NPC_RUN_MODE ?= dpi

ifeq ($(NPC_RUN_MODE),sram)
override NPC_HOME := $(AM_HOME)/../npc
IMG_HEX := $(NPC_HOME)/build/img.hex
run: insert-arg
	@python $(AM_HOME)/tools/bin2readmemh.py $(IMAGE).bin $(IMG_HEX)
	@echo "[riscv32-npc] load $(IMAGE).bin -> $(IMG_HEX)"
	@$(MAKE) -s -C $(NPC_HOME) run
else
override NPC_HOME := $(AM_HOME)/../riscv32e-npc
run: insert-arg
	$(NPC_HOME)/run-npc.sh $(IMAGE).bin  $(mainargs)
endif

.PHONY: insert-arg
