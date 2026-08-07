# NEMU 移植问题记录

## 1. `$readmemh` 路径对不上

**现象**：仿真跑到 timeout，pc=0x800000c8，实际程序没加载

**原因**：`inst_mem.v` 里 `$readmemh("../csrc/test.hex")` —— 仿真从 `npc/` 运行，`../csrc/` 等于向上找没找到

**修复**：改成 `$readmemh("csrc/test.hex", mem)`（相对 `npc/` 执行路径）

**文件**：`vsrc/inst_mem.v`

---

## 2. `$readmemh` 位宽不匹配

**现象**：二进制文件看起来加载了，但读到的是全 0

**原因**：`reg [7:0] mem` + `$readmemh(32bit_hex)` —— `$readmemh` 对 byte-wide 数组每行只读低 8 位

**修复**：`inst_mem` 改成 `reg [31:0] mem [0:32767]`（字宽数组，字寻址），`$readmemh` 直接加载 32-bit word

**文件**：`vsrc/inst_mem.v`

---

## 3. `initial` 多块执行顺序不确定

**现象**：需要默认程序和文件程序共存

**修复**：同一个 `initial` 块内先写默认值，再 `$readmemh` 覆盖

```verilog
initial begin
    mem[0] = ...;  // defaults first
    $readmemh(...); // overwrites if file exists
end
```

**文件**：`vsrc/inst_mem.v`

---

## 4. `npc.h` 缺 `extern "C"`

**现象**：g++ 报 `conflicting declaration ... with 'C' linkage`

**原因**：`npc.h` 被 C 文件（`main.c`）和 C++ 文件（`npc.cpp`）同时 include。C++ 编译时函数名被 mangle，跟 `extern "C"` 定义的符号对不上

**修复**：`npc.h` 加 `#ifdef __cplusplus extern "C" { ... } #endif`

**文件**：`csrc/npc.h`

---

## 5. Verilator 内部信号名不能直接访问

**现象**：`top->u_core__DOT__IR` 不存在、`top->u_core__DOT__ctrl_state` 编译失败

**原因**：Verilator 生成的 `Vtop.h` 只暴露顶层 `output` 端口，不暴露内部信号

**修复**：在不可综合的 debug 输出口引出：

```verilog
// top.v: 加 output ir_dbg, state_dbg
// core.v: assign ir_dbg = IR; assign state_dbg = ctrl_state;
// npc.cpp: top->ir_dbg, top->state_dbg
```

**文件**：`vsrc/top.v`, `vsrc/core.v`, `csrc/npc.cpp`

---

## 6. `main.cpp` 缓存未清理

**现象**：`No rule to make target '../csrc/main.cpp'`

**原因**：先前的 `main.cpp` 编译缓存（`.o`/`.d`）还在 build 目录，新的 `main.c` 没生成对应规则

**修复**：`make clean && make` 清掉旧缓存

---
