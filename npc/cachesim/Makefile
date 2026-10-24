# cachesim 独立编译 (不参与 Verilator, 也不影响 npc 主构建)

CXX      ?= g++
CXXFLAGS ?= -O2 -Wall
TARGET   := cachesim
SRCS     := cachesim.cpp

# 默认 trace (命令行可覆盖: make run TRACE=/tmp/trace_test.bin)
TRACE ?= ../build/itrace.bin
ARGS  ?=

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET) $(TRACE) $(ARGS)

clean:
	rm -f $(TARGET)

sweep: $(TARGET)
	@test -f $(TRACE) || { echo "[sweep] 找不到 $(TRACE): 先跑一次 npc 的 make run 生成 itrace.bin"; exit 1; }
	./$(TARGET) $(TRACE) --sweep


.PHONY: all run clean sweep
