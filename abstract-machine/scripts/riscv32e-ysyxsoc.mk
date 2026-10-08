include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/ysyxsoc.mk 

COMMON_CFLAGS += -march=rv32e_zicsr -mabi=ilp32e
LDFLAGS += -melf32lriscv
# LDFLAGS += --print-map        # 临时: 每次链接时打印映射表
COMMON_CFLAGS += -ffunction-sections -fdata-sections   # 每个函数/数据独立成段
LDFLAGS       += --gc-sections                          # 链接时删掉无引用的段

AM_SRCS += riscv/npc/libgcc/div.S \
           riscv/npc/libgcc/muldi3.S \
           riscv/npc/libgcc/multi3.c \
           riscv/npc/libgcc/ashldi3.c \
           riscv/npc/libgcc/unused.c
