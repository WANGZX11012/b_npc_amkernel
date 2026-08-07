`include "ctrl_defs.vh"

`ifndef USE_SRAM
// ── DPI-C 模式（仿真用） ──
import "DPI-C" function void pmem_write_u32(input int waddr, input int wdata);
import "DPI-C" function int  pmem_read_u32(input int raddr);
import "DPI-C" function void pmem_write_u8(input int waddr, input byte wdata);
import "DPI-C" function byte pmem_read_u8(input int raddr);
import "DPI-C" function void pmem_write_u16(input int waddr, input int wdata);
import "DPI-C" function int  pmem_read_u16(input int raddr);
`endif

module LSU (
  input  wire        clk,
  input  wire        mem_re,
  input  wire        mem_we,
  input  wire [1:0]  mem_width,
  input  wire        mem_signed,
  input  wire [31:0] wdata,
  input  wire [31:0] addr,
  input  wire [31:0] pc,
  output reg  [31:0] rdata
);

`ifdef USE_SRAM
  // ── SRAM 模式（综合用）：256×32b，组合读 + 同步写 ──
  reg [31:0] dmem [0:255];               // 256 × 32bit = 1KB
  wire [7:0] word_idx = addr[9:2];        // 字寻址

  // 组合读（保持单周期特性）
  always @(*) begin
    rdata = 32'h0;
    if (mem_re) begin
      case (mem_width)
        `MEM_BYTE: begin
          rdata = mem_signed ? {{24{dmem[word_idx][7]}}, dmem[word_idx][7:0]}
                             : {24'b0, dmem[word_idx][7:0]};
        end
        `MEM_HALF: begin
          rdata = mem_signed ? {{16{dmem[word_idx][15]}}, dmem[word_idx][15:0]}
                             : {16'b0, dmem[word_idx][15:0]};
        end
        `MEM_WORD: rdata = dmem[word_idx];
        default:   rdata = 32'h0;
      endcase
    end
  end

  // 同步写
  always @(posedge clk) begin
    if (mem_we) begin
      case (mem_width)
        `MEM_BYTE:  dmem[word_idx][7:0]   <= wdata[7:0];
        `MEM_HALF:  dmem[word_idx][15:0]  <= wdata[15:0];
        `MEM_WORD:  dmem[word_idx]        <= wdata;
        default: ;
      endcase
    end
  end

`else
  // ── DPI-C 模式（仿真用） ──
  always @(posedge clk) begin
    if (mem_we) begin
      case (mem_width)
        `MEM_BYTE:  pmem_write_u8 (addr, wdata[7:0]);
        `MEM_WORD:  pmem_write_u32(addr, wdata);
        `MEM_HALF:  pmem_write_u16(addr, wdata[15:0]);
        default: ;
      endcase
    end
  end

  always @(*) begin
    rdata = 32'h0;
    if (mem_re) begin
      case (mem_width)
        `MEM_BYTE: begin
          byte b = pmem_read_u8(addr);
          rdata = mem_signed ? {{24{b[7]}}, b} : {24'b0, b};
        end
        `MEM_HALF: begin
          logic [15:0] h = pmem_read_u16(addr) & 16'hFFFF;
          rdata = mem_signed ? {{16{h[15]}}, h} : {16'b0, h};
        end
        `MEM_WORD: rdata = pmem_read_u32(addr);
        default:   rdata = 32'h0;
      endcase
    end
  end
`endif

endmodule
