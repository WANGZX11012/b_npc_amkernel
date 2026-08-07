// B1 任务 2：256×32b 指令 SRAM，组合读（保持单周期特性）
module inst_sram (
  input  wire [31:0]  addr,     // 字节地址
  output wire [31:0]  inst      // 32-bit 指令
);

  reg [31:0] mem [0:255];       // 256 × 32bit = 1KB

  // 字寻址：忽略低 2 位
  wire [7:0] word_idx = addr[9:2];

  assign inst = mem[word_idx];

  // 仿真加载（仅 Verilator，综合时忽略）
`ifdef VERILATOR
  initial $readmemh("csrc/test.hex", mem);
`endif

endmodule
