CXX      ?= g++
CXXFLAGS ?= -O2 -Wall
TARGET   := cachesim
SRCS     := cachesim.cpp
CONF     := ../include/generated/autoconf.h
ITRACE    ?= ../build/itrace.bin
MTRACE   ?= ../build/mtrace.bin

ARGS     ?=

all: $(TARGET)

$(TARGET): $(SRCS) $(CONF)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

run: $(TARGET)
	@test -f $(ITRACE) || { echo "[run] 找不到 $(ITRACE), 先开 CONFIG_ITRACE 跑一次仿真"; exit 1; }
	@LSU_TRACE=$(MTRACE) ./$(TARGET) $(ITRACE) $(ARGS)


sweep: $(TARGET)
	@test -f $(ITRACE) || { echo "[sweep] 找不到 $(ITRACE)"; exit 1; }
	./$(TARGET) $(ITRACE) --sweep

clean:
	rm -f $(TARGET) $(SRCS:.cpp=.d)

.PHONY: all run clean sweep
