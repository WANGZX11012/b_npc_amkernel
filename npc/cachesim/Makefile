CXX      ?= g++
CXXFLAGS ?= -O2 -Wall
TARGET   := cachesim
SRCS     := cachesim.cpp
CONF     := ../include/generated/autoconf.h
TRACE    ?= ../build/itrace.bin
ARGS     ?=

all: $(TARGET)

$(TARGET): $(SRCS) $(CONF)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

run: $(TARGET)
	./$(TARGET) $(TRACE) $(ARGS)

sweep: $(TARGET)
	@test -f $(TRACE) || { echo "[sweep] 找不到 $(TRACE)"; exit 1; }
	./$(TARGET) $(TRACE) --sweep

clean:
	rm -f $(TARGET) $(SRCS:.cpp=.d)

.PHONY: all run clean sweep
