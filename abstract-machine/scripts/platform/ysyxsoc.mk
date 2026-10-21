AM_SRCS := riscv/ysyxsoc/start.S \
           riscv/ysyxsoc/trm.c

LDSCRIPTS += $(AM_HOME)/scripts/ysyxsoc0.ld      # ① MROM 链接(不是 ysyxsoc.ld)

image: image-dep
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -O binary $(IMAGE).elf $(IMAGE).bin

NPC_SOC_HOME ?= $(AM_HOME)/../npc/soc

run: image
	# ② 整个程序灌进 MROM(不再是只抽 .boot)
	@cp $(IMAGE).bin $(NPC_SOC_HOME)/mrom.img
	@$(MAKE) -s -C $(NPC_SOC_HOME) run IMG=$(IMAGE).bin
