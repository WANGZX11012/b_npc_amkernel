module top(
  input         clk,
  input         reset,
`ifndef USE_SRAM
  input  [31:0] inst,   // C++ 每拍喂进来的指令（DPI-C 模式）
`endif
  output [31:0] pc      // 给 C++ 取指地址
);

  wire [31:0] inst_wire; // 最终送给 core 的指令
  wire [31:0] inst_dbg;
  wire [31:0] a0_dbg;
  wire        invalid_dbg;

`ifdef USE_SRAM
  // SRAM 模式：指令从内部 inst_sram 取值
  inst_sram u_inst_sram (.addr(pc), .inst(inst_wire));
`else
  // DPI-C 模式：指令从外部 inst 端口来
  assign inst_wire = inst;
`endif

  core u_core(
    .clk        (clk),
    .reset      (reset),
    .inst       (inst_wire),
    .pc         (pc),
    .inst_dbg   (inst_dbg),
    .a0_dbg     (a0_dbg),
    .invalid_dbg(invalid_dbg)
  );

`ifndef USE_SRAM
  dpic_ebreak u_dpic(
    .clk   (clk),
    .inst  (inst_dbg),
    .pc    (pc),
    .r_a0  (a0_dbg)
  );

  dpic_invalid u_dpic_invalid(
    .clk    (clk),
    .reset  (reset),
    .invalid(invalid_dbg)
  );
`endif

endmodule
