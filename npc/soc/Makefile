# ══════════════════════════════════════════════════════════════════════════
#  npc/soc/Makefile — B2: 把 NPC 挂到 ysyxSoC 上做联合仿真
# ══════════════════════════════════════════════════════════════════════════
#
#  【这个文件是干嘛的】
#    把那条又长又难记的 verilator 命令写下来, 以后只敲 `make lint` 就行。
#    那条命令要编译: 17 个 CPU 文件 + 32 个 SoC/perip 文件 + 8 个选项。
#
#  【为什么不写在 npc/Makefile 里】
#    两个模式的顶层模块和 C 侧代码完全不同:
#      单跑 : 顶层 top,          C 侧 csrc/main.c + sdb + difftest
#      SoC  : 顶层 ysyxSoCFull,  C 侧另一套 tb
#    混在一个文件里, 每个变量都得写 ifeq 分支, 出问题极难定位。
#
#  【怎么用】(先进到 npc/soc 目录)
#    make lint    只做 elaboration + lint, 不生成可执行文件   ← 现在用这个
#    make build   生成仿真可执行文件(要等第七步写好 tb)
#    make run     跑仿真
#    make clean   删掉 build/
#
#  【Makefile 语法只有一条】
#      目标: 依赖
#      <TAB>命令          ← 行首必须是 TAB 键, 不能是空格!
#    读作: "要得到『目标』, 先确保『依赖』就绪, 然后执行『命令』"
#
#  【几个常用写法】
#    X = 值            定义变量; 用的时候写 $(X)
#    $(函数 参数...)   调用 make 自带函数: $(abspath ..) $(wildcard ..) $(filter-out ..)
#    $(shell 命令)     让 make 去跑一条 shell 命令, 把输出当成这个变量的值
#    $@ / $<           自动变量: $@ = 目标名, $< = 第一个依赖的文件名
#    @命令             行首加 @ = 执行这条命令, 但不要把它回显出来
#
#  ⚠ 变量定义的行尾不要写 # 注释: Makefile 里的 # 会连"续行符 \"一起吃掉,
#     导致下面那行被当成一条新语句。所以本文件注释一律单独成行。
# ══════════════════════════════════════════════════════════════════════════


# ═══════════════════════ 1. 名字和路径 ═══════════════════════

# 顶层模块名 —— 要求 9: 必须是 ysyxSoCFull
#   build/ysyxSoCFull.v 里还有个 ysyxSoCTop, 但它把 uart/gpio 等引脚全 tie 死了;
#   要求点名用 ysyxSoCFull, 因为它的引脚是真的(tb 可以驱动 uart_rx 之类)
TOPNAME   = ysyxSoCFull

# 生成物放哪。相对路径, 相对于"执行 make 时的目录"(= npc/soc)
BUILD_DIR = build

# 相对路径 —— 相对于"执行 make 时的目录"(即本文件所在的 npc/soc)。
# 不用 $(CURDIR)/$(abspath): 它们一旦展开失败, 报错只说"找不到文件", 极难查
#   (参考之前那次 /build/ysyxSoCFull.v 找不到的报错)
NPC_HOME = ..
SOC_HOME = ../../ysyxSoC


# ═══════════════ 2. SoC 源文件 → 改名副本 ═══════════════

# 输入: Chisel 生成的原文件(它里面例化的黑盒名是 ysyx_00000000)
SOC_SRC = $(SOC_HOME)/build/ysyxSoCFull.v

# 输出: 我们生成的副本(里面的黑盒名会被 sed 改成 ysyx_26020047)
SOC_V   = $(BUILD_DIR)/ysyxSoCFull.v


# ═══════════════ 3. perip —— 要求 5 ═══════════════

# $(shell find ...) 让 make 真的执行这条 shell 命令, 输出(一串 .v 路径)作为值
# 要求 5 说"perip 及子目录下所有 .v 都加入文件列表", 所以用 find 自动收集
#
# 为什么不用 -y <dir> 让 verilator 自己找模块? 因为 perip 里有"一个文件多个模块":
#   flash.v 里同时有 flash 和 flash_cmd 两个模块
# -y 是按"文件名 = 模块名"去猜文件位置的, 遇到一个文件装多个模块就容易漏,
# 所以显式列全部文件最稳(这也正是要求 5 让你列文件列表的原因)
PERIP_V = $(shell find $(SOC_HOME)/perip -name "*.v")


# ═══════════════ 4. 我们的 CPU —— vsrc 里的文件 ═══════════════

# $(wildcard ...) 把通配符展开成文件列表
# $(filter-out A,B) 从列表 B 里剔除列表 A 中的项
#
# 下面 4 个文件不能参与 SoC 构建, 每个都有硬理由:
#   top.v       单跑模式的顶层, 会和 ysyxSoCFull 争"谁是顶层";
#               而且它装的是 pc/ir_dbg/state_dbg 这些给 sdb/difftest 用的口
#   uart.v      SoC 模式下不例化; 另外它写了 import "DPI-C" uart_putchar,
#               编进来就必须由 C 侧实现这个函数, 否则链接报 undefined reference
#   rtc.v       同理(DPI-C rtc_time_us); 第九步若决定保留 RTC 再把它放回来
#   dpic_mem.v  同理(DPI-C dpic_mem_read/write); SoC 模式下主存走 SoC, 用不到它
NPC_SKIP = $(NPC_HOME)/vsrc/top.v \
           $(NPC_HOME)/vsrc/uart.v \
           $(NPC_HOME)/vsrc/rtc.v \
           $(NPC_HOME)/vsrc/dpic_mem.v

CPU_V = $(filter-out $(NPC_SKIP), $(wildcard $(NPC_HOME)/vsrc/*.v))


# ═══════════════ 5. 仿真 tb —— 第七步 ═══════════════

# 还没写, 所以现在 `make build` 会失败; `make lint` 不受影响(它不需要 tb)
TB_CPP = soc_tb.cpp


# ═══════════════ 6. verilator 的选项 ═══════════════
#
#   --top-module $(TOPNAME)   要求 9: 告诉 verilator 从哪个模块开始展开整颗设计
#                             (一颗 SoC 里有几十个模块, 不说顶层它不知道从哪起)
#
#   +define+YSYXSOC           传一个宏。core.v 里 `ifdef YSYXSOC 那几段据此生效:
#                             旁路内部 SRAM/UART, 把 AXI4 直通到顶层
#
#   --timescale "1ns/1ns"     要求 7: 给整个设计一个默认时间单位。
#                             Chisel 生成的代码里有 #0 这类语句, 没有 timescale 会刷警告
#
#   --no-timing               要求 7: 明确告诉 verilator "不要管时序(延时)"。
#                             perip 里有 #delay, verilator 本来就不模拟真实延时, 加上它安静些
#
#   -Wall                     打开全部警告
#   -Wno-fatal                警告不阻断编译。
#                             ⚠ 代价: 有它以后"编译过了"不代表没问题,
#                               每次都得自己 grep 警告(见文件末尾的检查方法)
#
#   -I<dir>                   要求 6: `include 的搜索路径。
#                             perip 的 uart_regs.v 里写了 `include "uart_defines.v",
#                             spi_top.v 里写了 `include "spi_defines.v", 如果文件不在同目录,
#                             就得用 -I 告诉它去哪找。
#                             (注意区分: -I 是"找 `include 的文件"; -y 是"找模块定义在哪个文件"。
#                              本文件只有一个 -I 家族, 没有 -y)
BASE_FLAGS = --top-module $(TOPNAME) \
             +define+YSYXSOC \
             --timescale "1ns/1ns" \
             --no-timing \
             -Wall -Wno-fatal \
             -I$(NPC_HOME)/vsrc \
             -I$(SOC_HOME)/perip/uart16550/rtl \
             -I$(SOC_HOME)/perip/spi/rtl


# ═══════════════ 7. 要编译的所有文件 ═══════════════

V_FILES = $(SOC_V) $(PERIP_V) $(CPU_V)


# ═══════════════ 8. 伪目标声明 ═══════════════

# lint/build/run/clean 都不是真实文件名, 声明成 .PHONY 让 make 每次都真的执行,
# 而不是去看"有没有一个叫 lint 的文件、它是不是比依赖新"
.PHONY: lint build run clean


# ═══════════════ 9. 规则: 生成改名后的 SoC 副本 ═══════════════

# 读法: "要得到 $(SOC_V), 先确保 $(SOC_SRC) 就绪; 然后执行下面三行"
#   $@ = 目标名   = build/ysyxSoCFull.v
#   $< = 第一个依赖 = ysyxSoC/build/ysyxSoCFull.v
#
# 为什么不直接改 ysyxSoC/build/ysyxSoCFull.v?
#   那是"生成物", 哪天重跑 make verilog 就没了, 而且它不属于我们的 git 仓库。
#   所以 sed 一份副本出来, 每次 make 自动生成, 可重复、可复现。
$(SOC_V): $(SOC_SRC)
	@mkdir -p $(BUILD_DIR)
	@sed 's/ysyx_00000000/ysyx_26020047/g' $< > $@
	@grep -q 'ysyx_26020047' $@ || (echo "sed 改名失败: 副本里没找到 ysyx_26020047"; exit 1)


# ═══════════════ 10. 目标: lint ═══════════════

# --lint-only: 只做 elaboration(展开+连接)和 lint(检查), 不生成 C++, 也不链接 C 函数。
# 好处: ① 不需要 tb  ② 不会撞上 flash_read/mrom_read 的 DPI 链接问题
# 第一次跑 SoC 模式就用它, 先把 RTL 层面的错误(含组合回环 UNOPTFLAT)挖出来
lint: $(SOC_V)
	verilator --lint-only $(BASE_FLAGS) $(V_FILES)


# ═══════════════ 11. 目标: build ═══════════════

#   --cc                  生成 C++ 代码
#   --exe                 生成可执行文件(所以必须有一个 C++ main, 就是 $(TB_CPP))
#   --build               生成完顺手把 C++ 编+链(等价于再 make -C build)
#   --Mdir $(BUILD_DIR)   生成物丢到哪个目录
#   -j 4                  并行编译。SoC 这么大, 不并行要等很久。
#                         (如果你本机报 unknown option, 换成 --build-jobs 4, 同一个意思)
#   --output-split 20000  把生成的 C++ 拆成多个文件, 每个不超过 20000 条语句。
#                         不拆的话 verilator 会把整颗 SoC 生成进一个巨大 .cpp,
#                         g++ 编它极慢、极吃内存 —— SoC 量级基本必加
#加了自动冲刷 防止
build: $(SOC_V) $(TB_CPP)
	verilator --cc --exe --build --Mdir  $(BUILD_DIR) --autoflush -j 4 --output-split 20000 \
	          $(BASE_FLAGS) $(V_FILES) $(TB_CPP)


# ═══════════════ 12. 目标: run ═══════════════

# verilator 生成的可执行文件名 = V + 顶层模块名, 所以是 build/VysyxSoCFull
IMG ?= test/char-test.bin

run: build
	./$(BUILD_DIR)/V$(TOPNAME) $(IMG)



# ═══════════════ 13. 目标: clean ═══════════════

clean:
	rm -rf $(BUILD_DIR)
	


# ═══════════════ 检查方法(不在 Makefile 里, 手动跑) ═══════════════
#
#   cd /home/wang/ysyx-workbench/npc/soc
#   make lint 2>&1 | tee /tmp/soc_lint.log      # 全部存下来, 别只瞄一眼
#
#   grep -iE "%Error"                          /tmp/soc_lint.log   # 必须为空
#   grep -iE "%Warning-(MULTIDRIVEN|UNOPTFLAT)" /tmp/soc_lint.log  # 必须为空(多驱动/组合回环)
#   grep -iE "%Warning-PINMISSING" /tmp/soc_lint.log | grep -E "vsrc/"   # 只看我们自己文件的悬空口
#
#   注意: ysyxSoCFull.v 是 Chisel 生成的, 它自带一大堆 /* unused */ 警告,
#         那不算我们的问题 —— 所以最后一条要 grep "vsrc/" 过滤。
