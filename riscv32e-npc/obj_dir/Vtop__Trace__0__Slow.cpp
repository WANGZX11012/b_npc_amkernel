// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"inst_wire",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"inst_dbg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"a0_dbg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+148,0,"invalid_dbg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"inst_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"a0_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+148,0,"invalid_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+70,0,"pc4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+149,0,"rs1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+150,0,"rs2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+151,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+3,0,"rd_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"alu_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+6,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"alu_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+152,0,"csr_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+153,0,"csr_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+9,0,"csr_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"csr_s_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+71,0,"csr_mtvec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"csr_mepc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"wb_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+12,0,"npc_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+13,0,"mem_re",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"mem_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"mem_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+16,0,"mem_signed",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+17,0,"idu_rs1_en_unused",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+18,0,"idu_rs2_en_unused",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+19,0,"branch_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+148,0,"idu_invalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+154,0,"r_data1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+155,0,"r_data2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+65,0,"alu_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+156,0,"branch_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+66,0,"wb_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+67,0,"rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"r_a0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_CSRFile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+169,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"csr_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+20,0,"ecall_trap",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+170,0,"ebreak_trap",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"mret_exec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+147,0,"ecall_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+154,0,"csr_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+153,0,"csr_idx",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+10,0,"csr_s_w",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+71,0,"csr_mtvec",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"csr_mepc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+152,0,"csr_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+152,0,"csr_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+73,0,"mcycle",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+1,0,"mvendroid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"marchid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+75,0,"mcause",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"mepc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+76,0,"mstatus",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+71,0,"mtvec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_exu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+154,0,"rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+155,0,"rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+7,0,"alu_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"alu_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+6,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+19,0,"branch_type",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+65,0,"alu_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+156,0,"branch_taken",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+157,0,"src1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+158,0,"src2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_idu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+146,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+149,0,"rs1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+150,0,"rs2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+151,0,"rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+17,0,"rs1_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+18,0,"rs2_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"rd_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"alu_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+7,0,"alu_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"mem_re",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"mem_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"mem_width",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+16,0,"mem_signed",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"wb_sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+12,0,"npc_sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+19,0,"branch_type",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+148,0,"invalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+153,0,"csr_idx",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+9,0,"csr_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"csr_s_w",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+171,0,"IMM_I",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+172,0,"IMM_S",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+173,0,"IMM_U",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+174,0,"IMM_B",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+175,0,"IMM_J",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+159,0,"opcode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+160,0,"funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+161,0,"funct7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+22,0,"imm_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+23,0,"is_jal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"is_jalr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+25,0,"is_bne",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"is_beq",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"is_bge",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"is_bgeu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+29,0,"is_blt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+30,0,"is_bltu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+31,0,"is_lui",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"is_lbu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"is_lw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"is_lb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+35,0,"is_lh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+36,0,"is_lhu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+37,0,"is_ebreak",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"is_csrrs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"is_csrrw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"is_ecall",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"is_mret",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+41,0,"is_fence",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"is_sb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"is_sw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+44,0,"is_sh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+45,0,"is_auipc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+46,0,"is_or",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+47,0,"is_ori",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+48,0,"is_xor",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+49,0,"is_xori",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+50,0,"is_add",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+51,0,"is_addi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+52,0,"is_sub",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+53,0,"is_slti",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+54,0,"is_sltiu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+55,0,"is_and",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"is_andi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"is_sra",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"is_srai",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+59,0,"is_srl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+60,0,"is_sll",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"is_slli",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+62,0,"is_srli",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+63,0,"is_sltu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+64,0,"is_slt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"illegal_shift_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+163,0,"imm_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+164,0,"imm_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+165,0,"imm_u",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"imm_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+167,0,"imm_j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_ifu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+65,0,"alu_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"npc_sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+156,0,"branch_taken",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+71,0,"csr_mtvec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"csr_mepc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+70,0,"pc4",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"inst_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+77,0,"pc_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+168,0,"next_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_lsu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"mem_re",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"mem_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"mem_width",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+16,0,"mem_signed",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+155,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+65,0,"addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+67,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+68,0,"b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::BYTE, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+69,0,"h",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_regfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+176,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+177,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+66,0,"w_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+151,0,"w_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+149,0,"r_addr1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+150,0,"r_addr2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+3,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+154,0,"r_data1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+155,0,"r_data2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"r_a0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("rf", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+78+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rf_read", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+111+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+143,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_wbu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+70,0,"pc4",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+65,0,"alu_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+67,0,"mem_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+152,0,"csr_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"wb_sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+66,0,"wb_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_dpic", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"r_a0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+178,0,"EBREAK",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_dpic_invalid", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+144,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+148,0,"invalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+169,(0x0000000cU),32);
    bufp->fullBit(oldp+170,(0U));
    bufp->fullCData(oldp+171,(0U),3);
    bufp->fullCData(oldp+172,(1U),3);
    bufp->fullCData(oldp+173,(2U),3);
    bufp->fullCData(oldp+174,(3U),3);
    bufp->fullCData(oldp+175,(4U),3);
    bufp->fullIData(oldp+176,(5U),32);
    bufp->fullIData(oldp+177,(0x00000020U),32);
    bufp->fullIData(oldp+178,(0x00100073U),32);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+1,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid),32);
    bufp->fullIData(oldp+2,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__marchid),32);
    bufp->fullBit(oldp+3,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                       | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))));
    bufp->fullIData(oldp+4,(vlSelfRef.top__DOT__u_core__DOT__imm),32);
    bufp->fullCData(oldp+5,(vlSelfRef.top__DOT__u_core__DOT__alu_op),4);
    bufp->fullBit(oldp+6,(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm));
    bufp->fullBit(oldp+7,(vlSelfRef.top__DOT__u_core__DOT__alu_en));
    bufp->fullBit(oldp+8,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                             | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))));
    bufp->fullBit(oldp+9,(vlSelfRef.top__DOT__u_core__DOT__csr_wen));
    bufp->fullBit(oldp+10,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs));
    bufp->fullCData(oldp+11,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai) 
                                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli) 
                                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi) 
                                                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl) 
                                                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7)))))))))))))))))))
                               ? 0U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3)
                                        ? 1U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                                       | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6))))
                                                 ? 2U
                                                 : 
                                                ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui)
                                                  ? 3U
                                                  : 
                                                 ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4)
                                                   ? 4U
                                                   : 0U)))))),3);
    bufp->fullCData(oldp+12,(vlSelfRef.top__DOT__u_core__DOT__npc_sel),3);
    bufp->fullBit(oldp+13,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0) 
                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2)))));
    bufp->fullBit(oldp+14,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh))));
    bufp->fullCData(oldp+15,(vlSelfRef.top__DOT__u_core__DOT__mem_width),2);
    bufp->fullBit(oldp+16,(vlSelfRef.top__DOT__u_core__DOT__mem_signed));
    bufp->fullBit(oldp+17,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_10) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_8) 
                                                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))))))))))))))))))))));
    bufp->fullBit(oldp+18,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and) 
                                                                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl))))))))))))))))))));
    bufp->fullCData(oldp+19,(vlSelfRef.top__DOT__u_core__DOT__branch_type),3);
    bufp->fullBit(oldp+20,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))));
    bufp->fullBit(oldp+21,((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))));
    bufp->fullCData(oldp+22,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type),3);
    bufp->fullBit(oldp+23,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal));
    bufp->fullBit(oldp+24,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr));
    bufp->fullBit(oldp+25,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne));
    bufp->fullBit(oldp+26,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq));
    bufp->fullBit(oldp+27,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge));
    bufp->fullBit(oldp+28,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu));
    bufp->fullBit(oldp+29,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt));
    bufp->fullBit(oldp+30,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu));
    bufp->fullBit(oldp+31,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui));
    bufp->fullBit(oldp+32,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu));
    bufp->fullBit(oldp+33,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw));
    bufp->fullBit(oldp+34,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb));
    bufp->fullBit(oldp+35,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh));
    bufp->fullBit(oldp+36,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu));
    bufp->fullBit(oldp+37,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak));
    bufp->fullBit(oldp+38,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw));
    bufp->fullBit(oldp+39,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall));
    bufp->fullBit(oldp+40,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret));
    bufp->fullBit(oldp+41,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence));
    bufp->fullBit(oldp+42,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb));
    bufp->fullBit(oldp+43,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw));
    bufp->fullBit(oldp+44,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh));
    bufp->fullBit(oldp+45,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc));
    bufp->fullBit(oldp+46,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or));
    bufp->fullBit(oldp+47,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori));
    bufp->fullBit(oldp+48,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor));
    bufp->fullBit(oldp+49,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori));
    bufp->fullBit(oldp+50,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add));
    bufp->fullBit(oldp+51,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi));
    bufp->fullBit(oldp+52,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub));
    bufp->fullBit(oldp+53,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti));
    bufp->fullBit(oldp+54,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu));
    bufp->fullBit(oldp+55,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and));
    bufp->fullBit(oldp+56,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi));
    bufp->fullBit(oldp+57,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra));
    bufp->fullBit(oldp+58,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai));
    bufp->fullBit(oldp+59,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl));
    bufp->fullBit(oldp+60,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll));
    bufp->fullBit(oldp+61,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli));
    bufp->fullBit(oldp+62,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli));
    bufp->fullBit(oldp+63,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu));
    bufp->fullBit(oldp+64,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt));
    bufp->fullIData(oldp+65,(vlSelfRef.top__DOT__u_core__DOT__alu_result),32);
    bufp->fullIData(oldp+66,(vlSelfRef.top__DOT__u_core__DOT__wb_data),32);
    bufp->fullIData(oldp+67,(vlSelfRef.top__DOT__u_core__DOT__rdata),32);
    bufp->fullCData(oldp+68,(vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT__unnamedblk1__DOT__b),8);
    bufp->fullSData(oldp+69,(vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT__unnamedblk2__DOT__h),16);
    bufp->fullIData(oldp+70,(((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg)),32);
    bufp->fullIData(oldp+71,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec),32);
    bufp->fullIData(oldp+72,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc),32);
    bufp->fullQData(oldp+73,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle),64);
    bufp->fullIData(oldp+75,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause),32);
    bufp->fullIData(oldp+76,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus),32);
    bufp->fullIData(oldp+77,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg),32);
    bufp->fullIData(oldp+78,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0]),32);
    bufp->fullIData(oldp+79,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[1]),32);
    bufp->fullIData(oldp+80,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[2]),32);
    bufp->fullIData(oldp+81,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[3]),32);
    bufp->fullIData(oldp+82,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[4]),32);
    bufp->fullIData(oldp+83,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[5]),32);
    bufp->fullIData(oldp+84,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[6]),32);
    bufp->fullIData(oldp+85,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[7]),32);
    bufp->fullIData(oldp+86,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[8]),32);
    bufp->fullIData(oldp+87,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[9]),32);
    bufp->fullIData(oldp+88,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[10]),32);
    bufp->fullIData(oldp+89,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[11]),32);
    bufp->fullIData(oldp+90,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[12]),32);
    bufp->fullIData(oldp+91,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[13]),32);
    bufp->fullIData(oldp+92,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[14]),32);
    bufp->fullIData(oldp+93,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[15]),32);
    bufp->fullIData(oldp+94,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[16]),32);
    bufp->fullIData(oldp+95,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[17]),32);
    bufp->fullIData(oldp+96,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[18]),32);
    bufp->fullIData(oldp+97,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[19]),32);
    bufp->fullIData(oldp+98,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[20]),32);
    bufp->fullIData(oldp+99,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[21]),32);
    bufp->fullIData(oldp+100,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[22]),32);
    bufp->fullIData(oldp+101,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[23]),32);
    bufp->fullIData(oldp+102,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[24]),32);
    bufp->fullIData(oldp+103,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[25]),32);
    bufp->fullIData(oldp+104,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[26]),32);
    bufp->fullIData(oldp+105,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[27]),32);
    bufp->fullIData(oldp+106,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[28]),32);
    bufp->fullIData(oldp+107,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[29]),32);
    bufp->fullIData(oldp+108,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[30]),32);
    bufp->fullIData(oldp+109,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[31]),32);
    bufp->fullIData(oldp+110,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read
                              [0x0aU]),32);
    bufp->fullIData(oldp+111,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0]),32);
    bufp->fullIData(oldp+112,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[1]),32);
    bufp->fullIData(oldp+113,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[2]),32);
    bufp->fullIData(oldp+114,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[3]),32);
    bufp->fullIData(oldp+115,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[4]),32);
    bufp->fullIData(oldp+116,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[5]),32);
    bufp->fullIData(oldp+117,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[6]),32);
    bufp->fullIData(oldp+118,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[7]),32);
    bufp->fullIData(oldp+119,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[8]),32);
    bufp->fullIData(oldp+120,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[9]),32);
    bufp->fullIData(oldp+121,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[10]),32);
    bufp->fullIData(oldp+122,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[11]),32);
    bufp->fullIData(oldp+123,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[12]),32);
    bufp->fullIData(oldp+124,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[13]),32);
    bufp->fullIData(oldp+125,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[14]),32);
    bufp->fullIData(oldp+126,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[15]),32);
    bufp->fullIData(oldp+127,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[16]),32);
    bufp->fullIData(oldp+128,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[17]),32);
    bufp->fullIData(oldp+129,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[18]),32);
    bufp->fullIData(oldp+130,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[19]),32);
    bufp->fullIData(oldp+131,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[20]),32);
    bufp->fullIData(oldp+132,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[21]),32);
    bufp->fullIData(oldp+133,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[22]),32);
    bufp->fullIData(oldp+134,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[23]),32);
    bufp->fullIData(oldp+135,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[24]),32);
    bufp->fullIData(oldp+136,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[25]),32);
    bufp->fullIData(oldp+137,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[26]),32);
    bufp->fullIData(oldp+138,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[27]),32);
    bufp->fullIData(oldp+139,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[28]),32);
    bufp->fullIData(oldp+140,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[29]),32);
    bufp->fullIData(oldp+141,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[30]),32);
    bufp->fullIData(oldp+142,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[31]),32);
    bufp->fullIData(oldp+143,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__i),32);
    bufp->fullBit(oldp+144,(vlSelfRef.clk));
    bufp->fullBit(oldp+145,(vlSelfRef.reset));
    bufp->fullIData(oldp+146,(vlSelfRef.inst),32);
    bufp->fullIData(oldp+147,(vlSelfRef.pc),32);
    bufp->fullBit(oldp+148,((1U & ((~ ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak) 
                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2) 
                                                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
                                                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence) 
                                                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret)))))))))))))))))))))))))))) 
                                   | (IData)(((0x02000013U 
                                               == (0x0200007fU 
                                                   & vlSelfRef.inst)) 
                                              & ((1U 
                                                  == 
                                                  (7U 
                                                   & (vlSelfRef.inst 
                                                      >> 0x0000000cU))) 
                                                 | (5U 
                                                    == 
                                                    (7U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x0000000cU))))))))));
    bufp->fullCData(oldp+149,((0x0000001fU & (vlSelfRef.inst 
                                              >> 0x0000000fU))),5);
    bufp->fullCData(oldp+150,((0x0000001fU & (vlSelfRef.inst 
                                              >> 0x00000014U))),5);
    bufp->fullCData(oldp+151,((0x0000001fU & (vlSelfRef.inst 
                                              >> 7U))),5);
    bufp->fullIData(oldp+152,(vlSelfRef.top__DOT__u_core__DOT__csr_data),32);
    bufp->fullSData(oldp+153,((vlSelfRef.inst >> 0x00000014U)),12);
    bufp->fullIData(oldp+154,(vlSelfRef.top__DOT__u_core__DOT__r_data1),32);
    bufp->fullIData(oldp+155,(vlSelfRef.top__DOT__u_core__DOT__r_data2),32);
    bufp->fullBit(oldp+156,(((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                              ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                 == vlSelfRef.top__DOT__u_core__DOT__r_data2)
                              : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                  ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                     != vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                  : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                      ? VL_GTES_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                      : ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                          ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                             >= vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                          : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                              ? VL_LTS_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                              : ((5U 
                                                  == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                                 & (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                                    < vlSelfRef.top__DOT__u_core__DOT__r_data2)))))))));
    bufp->fullIData(oldp+157,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                  | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))
                                ? vlSelfRef.pc : vlSelfRef.top__DOT__u_core__DOT__r_data1)),32);
    bufp->fullIData(oldp+158,(((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm)
                                ? vlSelfRef.top__DOT__u_core__DOT__imm
                                : vlSelfRef.top__DOT__u_core__DOT__r_data2)),32);
    bufp->fullCData(oldp+159,((0x0000007fU & vlSelfRef.inst)),7);
    bufp->fullCData(oldp+160,((7U & (vlSelfRef.inst 
                                     >> 0x0000000cU))),3);
    bufp->fullCData(oldp+161,((vlSelfRef.inst >> 0x00000019U)),7);
    bufp->fullBit(oldp+162,((IData)(((0x02000013U == 
                                      (0x0200007fU 
                                       & vlSelfRef.inst)) 
                                     & ((1U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0x0000000cU))) 
                                        | (5U == (7U 
                                                  & (vlSelfRef.inst 
                                                     >> 0x0000000cU))))))));
    bufp->fullIData(oldp+163,((((- (IData)((vlSelfRef.inst 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (vlSelfRef.inst 
                                                   >> 0x00000014U))),32);
    bufp->fullIData(oldp+164,((((- (IData)((vlSelfRef.inst 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (
                                                   (0x00000fe0U 
                                                    & (vlSelfRef.inst 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.inst 
                                                         >> 7U))))),32);
    bufp->fullIData(oldp+165,((0xfffff000U & vlSelfRef.inst)),32);
    bufp->fullIData(oldp+166,((((- (IData)((vlSelfRef.inst 
                                            >> 0x0000001fU))) 
                                << 0x0000000dU) | (
                                                   (((2U 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000001eU)) 
                                                     | (1U 
                                                        & (vlSelfRef.inst 
                                                           >> 7U))) 
                                                    << 0x0000000bU) 
                                                   | ((0x000007e0U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x00000014U)) 
                                                      | (0x0000001eU 
                                                         & (vlSelfRef.inst 
                                                            >> 7U)))))),32);
    bufp->fullIData(oldp+167,(((((0x00000ffeU & ((- (IData)(
                                                            (vlSelfRef.inst 
                                                             >> 0x0000001fU))) 
                                                 << 1U)) 
                                 | (vlSelfRef.inst 
                                    >> 0x0000001fU)) 
                                << 0x00000014U) | (
                                                   (((0x000001feU 
                                                      & (vlSelfRef.inst 
                                                         >> 0x0000000bU)) 
                                                     | (1U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x00000014U))) 
                                                    << 0x0000000bU) 
                                                   | (0x000007feU 
                                                      & (vlSelfRef.inst 
                                                         >> 0x00000014U))))),32);
    bufp->fullIData(oldp+168,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))
                                ? (0xfffffffeU & vlSelfRef.top__DOT__u_core__DOT__alu_result)
                                : (((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel)) 
                                    & ((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                        ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                           == vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                        : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                            ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                               != vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                            : ((2U 
                                                == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                ? VL_GTES_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                                : (
                                                   (3U 
                                                    == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                    ? 
                                                   (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                                    >= vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                     ? 
                                                    VL_LTS_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__r_data2)
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                                     & (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                                        < vlSelfRef.top__DOT__u_core__DOT__r_data2))))))))
                                    ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                                    : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))
                                        ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                                        : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))
                                            ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec
                                            : ((5U 
                                                == (IData)(vlSelfRef.top__DOT__u_core__DOT__npc_sel))
                                                ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                                                : ((IData)(4U) 
                                                   + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg))))))),32);
}
