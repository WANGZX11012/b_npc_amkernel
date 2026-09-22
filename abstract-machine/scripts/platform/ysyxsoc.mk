AM_SRCS := riscv/ysyxsoc/start.S \
           riscv/ysyxsoc/trm.c \


LDSCRIPTS += $(AM_HOME)/scripts/ysyxsoc.ld

image: image-dep
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -O binary $(IMAGE).elf $(IMAGE).bin

NPC_SOC_HOME ?= $(AM_HOME)/../npc/soc

run: image
	@echo "[ysyxsoc] run $(IMAGE).bin on ysyxSoC"
	@$(MAKE) -s -C $(NPC_SOC_HOME) run IMG=$(IMAGE).bin
