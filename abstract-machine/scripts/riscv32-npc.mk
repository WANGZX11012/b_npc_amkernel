include $(AM_HOME)/scripts/isa/riscv.mk
NPC_RUN_MODE := sram
include $(AM_HOME)/scripts/platform/npc.mk
COMMON_CFLAGS += -march=rv32e_zicsr_zifencei -mabi=ilp32e  # 加 zifencei 以支持 fence.i
LDFLAGS       += -melf32lriscv                    # overwrite
AM_SRCS += riscv/npc/libgcc/div.S \
           riscv/npc/libgcc/muldi3.S \
           riscv/npc/libgcc/multi3.c \
           riscv/npc/libgcc/ashldi3.c \
           riscv/npc/libgcc/unused.c
