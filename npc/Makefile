TOPNAME = top
BUILD_DIR = build

VSRCS  = $(wildcard vsrc/*.v)
VHSRCS = $(wildcard vsrc/*.vh)
CSRCS  = csrc/main.cpp

VERILATOR_FLAGS = --cc --exe --build --trace --Mdir $(BUILD_DIR) \
                  -I$(abspath vsrc) \
                  -Wall -Wno-fatal \
                  --top-module $(TOPNAME)

.PHONY: all sim wave clean

all:
	verilator $(VERILATOR_FLAGS) $(VSRCS) $(CSRCS)

sim: all
	./$(BUILD_DIR)/V$(TOPNAME)

wave:
	gtkwave $(BUILD_DIR)/sim.vcd &

clean:
	rm -rf $(BUILD_DIR)
