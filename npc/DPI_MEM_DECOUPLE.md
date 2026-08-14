# DPI-C 内存与 NEMU 解耦改造记录

> 适用范围：多周期 NPC（`/home/wang/ysyx-workbench/npc/`）
> 改造目标：让 DUT 的物理内存真相独立存在于 C++ 侧 `pmem_words[]` 数组，**不再借用 NEMU 的 `pmem`**，从而使内存比对（difftest）变成"两份独立内存"的比对，而不是"自己比自己"。

---

## 0. 先说结论：之前的设计错在哪

原 dpic 内存后端通过 `ref_difftest_memcpy(MEM_BASE, ..., DIFFTEST_TO_REF)` 把镜像写进 **NEMU 的 `pmem`**，然后 DUT 的读/写又经 DPI-C 回到 **NEMU 的 `pmem`**。

这是**错的**，理由：

1. **内存比对失去意义**。一旦开启 difftest，DUT 的内存来源和 REF 的内存来源是**同一块 NEMU `pmem`**。比对时"DUT 内存"和"REF 内存"是同一份数据，等于自己比自己，永远一致，发现不了 DUT 访存逻辑的 bug。
2. **违反"独立真相"原则**。正确的 difftest 必须保证：
   - DUT 内存 = DUT 自己持有的数组（`pmem_words[]`）；
   - REF 内存 = NEMU 的 `pmem`；
   - 两者只在**初始化时单向同步一次**（DUT → REF），之后各跑各的，跑完再比。
3. **你的单周期实现（`riscv32e-npc`）就是对的参照**：它在 C++ 侧直接 `pmem_words[]` 当物理内存真相，不碰 NEMU。多周期应该和它同构。

> 正确做法：**DUT 内存真相在 C++ `pmem_words[]`；difftest 开启时，仅用 `dpi_pmem_copy_out()` 把 DUT 内存单向拷给 NEMU `pmem` 一次**，之后 DUT 的 store/load 永远只改 `pmem_words[]`，不回写 NEMU。

---

## 1. 整体架构（改造后）

```
                        ┌─────────────────────────────┐
                        │         C++ 仿真进程         │
                        │                             │
  取指/访存请求          │   pmem_words[]  (DUT 真相)  │
  AXI4-Lite ───────────►│       128 MiB 数组          │
        │                │        ▲         │          │
        │                │        │         │ DPI-C    │
        ▼                │   dpic_mem_read/ │          │
   dpic_mem.v ──────────┼──► write() ◄──────┘          │
   (AXI-Lite slave)     │                             │
                        │   ┌──────── difftest 开启时 ┐ │
                        │   │ dpi_pmem_copy_out()     │ │
                        │   │   (DUT→REF, 仅初始化)  │ │
                        │   └──────────┬─────────────┘ │
                        │              ▼               │
                        │   ref_difftest_memcpy(TO_REF)│
                        │              ▼               │
                        │   NEMU pmem (REF 真相)       │
                        └─────────────────────────────┘
```

关键差异（对比改造前）：

| 项 | 改造前（错） | 改造后（对） |
|---|---|---|
| DUT 内存真相 | NEMU `pmem` | C++ `pmem_words[]` |
| store 落点 | NEMU `pmem` | `pmem_words[]` |
| 内存比对 | DUT 与 REF 同块内存，无意义 | DUT 与 REF 各持一份，比对有意义 |
| 初始化同步 | 镜像直接写 NEMU `pmem` | 镜像先填 `pmem_words[]`，再单向拷给 NEMU |

---

## 2. 模块/文件功能表

| 行号 | 文件 | 一句功能 |
|---|---|---|
| — | `csrc/dpic_mem.h` | 声明 DUT 内存后端接口，明确 DUT 内存独立、不依赖 NEMU |
| — | `csrc/dpic_mem.cpp` | 持有 `pmem_words[]`，实现 load/读写/拷出，是 DUT 内存唯一真相 |
| — | `csrc/difftest.cpp` | 加载 REF `.so`；`load_image_bin` 无条件填 DUT，开 difftest 时再单向同步 REF |
| — | `csrc/monitor/monitor.c` | 无条件调用 `difftest_init` 加载镜像（DPI_MEM 下必须有镜像） |
| — | `Makefile` | 去掉"DPI_MEM 强制依赖 DIFFTEST"约束，二者解耦 |
| — | `vsrc/dpic_mem.v` | AXI-Lite slave；写提交直接用当拍 `wdata`，修复旧值 bug |
| — | `vsrc/core.v` | 修正 `pmem_sel` 段判断，覆盖 `0x80~0x87` 全 128MB（含栈区） |

---

## 3. 逐文件详细改动

### 3.1 `csrc/dpic_mem.h` —— 重写接口声明，斩断 NEMU 依赖

**改动要点**：整个头文件的注释和接口语义从"DUT 内存存在 NEMU pmem"改为"DUT 内存是 C++ 侧独立数组"。

关键声明（第 11-35 行）：

```c
// DUT 物理内存基址 (与 NEMU CONFIG_MBASE 一致, 仅用于地址映射, 不依赖 NEMU)
#define DPI_PMEM_BASE 0x80000000u

bool dpi_load_image(const char *path);          // 由镜像加载填充 DUT 内存
void dpi_load_bin(const uint8_t *buf, size_t len); // raw .bin 线性字节填进 pmem_words[]
void dpi_init_pmem(size_t bytes);               // 无镜像时的兜底初始化
void dpi_pmem_copy_out(void *dst, size_t bytes);// 把 DUT 内存拷出, 供 difftest 初始化 REF
void dpic_mem_read(unsigned long long addr, unsigned int *rdata);  // 被 dpic_mem.v 调用
void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask); // 被 dpic_mem.v 调用
```

**为什么这样改**：原接口是"DUT 经 DPI-C 读写 NEMU pmem"的语义，会诱导后续调用者继续走 `ref_difftest_memcpy`。重写后接口名和注释都表明内存真相在 DUT 自己手上，`dpi_pmem_copy_out` 是**唯一**通往 NEMU 的出口，且方向固定 DUT→REF。

---

### 3.2 `csrc/dpic_mem.cpp` —— 真正持有物理内存，彻底不引用 NEMU

**改动要点**：删除所有对 `ref_difftest_memcpy` / NEMU `pmem` 的引用，改为本地 `pmem_words[]` 数组。

**(a) 内存本体（第 13-17 行）**

```cpp
static const size_t DPI_PMEM_MAX_WORDS = (128u * 1024u * 1024u) / 4u;  // 128 MiB
static uint32_t pmem_words[DPI_PMEM_MAX_WORDS] = {0};
static size_t   pmem_words_size = 0;  // 实际已初始化字数 (用于越界检查)
```

与单周期 `riscv32e-npc/csrc/dpic.cpp` 的 `pmem_words[]` 同构 —— DUT 内存独立真相。

**(b) 地址映射（第 22-25 行）**

```cpp
static uint32_t dpi_addr_to_index(uint32_t addr)
{
  return (addr - DPI_PMEM_BASE) >> 2;   // DPI_PMEM_BASE = 0x80000000
}
```

与 NEMU `ref.c` 的 `guest_to_host(paddr) = pmem + paddr - CONFIG_MBASE` 严格一致：**不做任何低位地址折回**（NEMU 侧也无折回）。传入的 `addr` 必须是物理地址。

**(c) `dpi_load_bin` 逐字节填（第 74-83 行）**

```cpp
void dpi_load_bin(const uint8_t *buf, size_t len)
{
  if (buf == nullptr || len == 0) return;
  uint8_t *base = reinterpret_cast<uint8_t *>(pmem_words);  // 当字节数组用
  size_t n = len;
  if (n > DPI_PMEM_MAX_WORDS * sizeof(uint32_t))
    n = DPI_PMEM_MAX_WORDS * sizeof(uint32_t);
  for (size_t i = 0; i < n; i++) base[i] = buf[i];   // 逐字节落盘
  pmem_words_size = (n + 3) / sizeof(uint32_t);
}
```

**为什么逐字节而不是直接 `memcpy` 一个 `uint32` 数组**：直接把 `uint32` 重组到 `pmem_words[]` 会引入字节序/对齐歧义。逐字节填等价于 NEMU 的 `memcpy(guest_to_host(MEM_BASE), buf, rd)`（guest_to_host 返回字节指针，逐字节落盘），语义完全对齐。

**(d) `dpi_pmem_copy_out` 单向拷出（第 95-102 行）**

```cpp
void dpi_pmem_copy_out(void *dst, size_t bytes)
{
  if (dst == nullptr || bytes == 0) return;
  size_t n = bytes;
  size_t maxn = pmem_words_size * sizeof(uint32_t);
  if (n > maxn) n = maxn;
  memcpy(dst, pmem_words, n);
}
```

这是 DUT→REF 的**唯一**出口，只在 `difftest.cpp` 初始化时调用一次。

**(e) `dpic_mem_read` / `dpic_mem_write`（第 107-134 行）**

```cpp
void dpic_mem_read(unsigned long long addr, unsigned int *rdata)
{
  if (rdata == nullptr) return;
  uint32_t idx = dpi_addr_to_index((uint32_t)addr);
  if (idx >= pmem_words_size) { *rdata = 0; return; }
  *rdata = pmem_words[idx];   // 返回对齐字, 由 LSU 用 addr[1:0] 选字节
}

void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask)
{
  uint32_t idx = dpi_addr_to_index((uint32_t)addr);
  if (idx >= DPI_PMEM_MAX_WORDS) return;
  uint32_t old = pmem_words[idx];
  uint8_t *p = (uint8_t *)&old;
  if (wmask & 0x1) p[0] = uint8_t(wdata >> 0);   // 小端: 低字节在低地址
  if (wmask & 0x2) p[1] = uint8_t(wdata >> 8);
  if (wmask & 0x4) p[2] = uint8_t(wdata >> 16);
  if (wmask & 0x8) p[3] = uint8_t(wdata >> 24);
  pmem_words[idx] = old;                          // 按 wmask 合并写回 DUT 内存
  if (idx + 1 > pmem_words_size) pmem_words_size = idx + 1;
}
```

读返回对齐字（LSU 用 `addr[1:0]` 选字节）；写按 `wmask` 合并字节，**只改 `pmem_words[]`，绝不回写 NEMU**。

---

### 3.3 `csrc/difftest.cpp` —— `load_image_bin` 无条件填 DUT，再单向同步 REF

**改动要点**：把 `load_image_bin` 从 `#if ENABLE_DIFFTEST` 块里**移出来**，放到文件前部无条件定义；内部先填 DUT，再在 `#if ENABLE_DIFFTEST` 内同步 REF。

**(a) `load_image_bin` 移出 `#if`（第 66-103 行）**

```cpp
static void load_image_bin(const char *img_path)
{
  // ... 打开 .bin, fread 到 buf ...
  if (rd > 0) {
    // ① 先把镜像载进 DUT 自己的 pmem_words[] (DUT 内存真相, 无条件执行)
    dpi_load_bin(buf, (size_t)rd);
#if ENABLE_DIFFTEST
    // ② 再把 DUT 内存拷出, 同步给 REF (NEMU pmem). 方向: DUT -> REF
    uint8_t *out = new uint8_t[rd];
    dpi_pmem_copy_out(out, (size_t)rd);
    ref_difftest_memcpy(MEM_BASE, out, rd, DIFFTEST_TO_REF);
    delete[] out;
#endif
  }
  delete[] buf;
}
```

**为什么必须移出 `#if`**：原代码把 `load_image_bin` 锁在 `ENABLE_DIFFTEST` 内，关掉 difftest 时 DUT 根本不加载镜像，`pmem_words[]` 全 0，纯 DUT 跑直接 BAD TRAP。移出后无论开不开 difftest，DUT 都有镜像。

**(b) 关 difftest 的兜底 `difftest_init`（第 250-254 行）**

```cpp
void difftest_init(uint32_t dut_pc, const char *img_path)
{
  (void)dut_pc;
  load_image_bin(img_path);   // 原为空函数, 现改为真正加载镜像
}
```

原 `#else` 分支 `difftest_init` 是空函数，DUT 无内存；现改为调用 `load_image_bin`。

**(c) `difftest_init`（开 difftest 时，第 192-211 行）**

顺序：① `load_ref_so` → ② `load_image_bin`（内部先填 DUT 再同步 REF）→ ③ `ref_difftest_regcpy` 同步寄存器。注释也同步改为"DUT 内存 → NEMU pmem"。

---

### 3.4 `csrc/monitor/monitor.c` —— 无条件加载镜像

**改动要点**：去掉 `difftest_init` 外面的 `#if ENABLE_DIFFTEST` 包裹，改为无条件调用。

```c
#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif
  // DPI_MEM 模式下 DUT 物理内存在 C++ 侧 pmem_words[], 必须有镜像来源,
  // 故无论是否开 difftest, 都要调 difftest_init 加载镜像
  difftest_init(npc_pc(), img_path);
```

**为什么**：DPI_MEM 下 DUT 内存真相在 C++ 数组，没有镜像 DUT 就是空内存。无论 difftest 开关如何，都必须先加载镜像。

---

### 3.5 `Makefile` —— 去掉 DPI_MEM 强制依赖 DIFFTEST 的约束

**改动要点**：删除原"DPI_MEM 依赖 NEMU pmem，必须开启 DIFFTEST"的强制逻辑，改为解耦说明（第 38-40 行）：

```make
# DPI_MEM 的内存由 C++ 侧 dpi_pmem_words[] 自己持有 (见 csrc/dpic_mem.cpp),
# 不依赖 NEMU pmem, 因此 DPI_MEM 与 DIFFTEST 解耦, 二者可独立开关。
# 若同时开 DIFFTEST, 由 difftest.cpp 用 dpi_pmem_copy_out() 把 DUT 内存同步给 REF。
```

`CONFIG_DPI_MEM` 与 `CONFIG_DIFFTEST` 现在是两条独立 menuconfig 项（`auto.conf` 中 `CONFIG_DPI_MEM=y`、`CONFIG_DIFFTEST=y` 可各自开关）。

---

### 3.6 `vsrc/dpic_mem.v` —— 修复写提交旧值 bug

**改动要点**：删除 `w_data_latch` 延迟锁存寄存器，写提交直接用当拍 `wdata`。

**原 bug（错误写法）**：

```verilog
reg [31:0] w_data_latch;
always @(posedge clk)
  if (awvalid && awready) w_data_latch <= wdata;   // 非阻塞, 当拍不更新
  if (aw_recv && wvalid && wready)
    dpic_mem_write({32'b0, aw_addr_latch}, w_data_latch, {4'b0, w_mask_latch}); // 同拍读到旧值 0
```

当 AW 与 W **同拍到达**时，`w_data_latch` 当拍还是上一笔的旧值（0），导致 store 写进 `pmem_words[]` 的数据全是 0。

**修复（第 49-56、94-103 行）**：

```verilog
reg        aw_recv;
reg [31:0] aw_addr_latch;
reg [3:0]  w_mask_latch;
// 注意: 不能用 w_data_latch 延迟锁存再提交 —— 当 AW/W 同拍到达时,
// 非阻塞赋值的 w_data_latch 当拍未更新, 提交会用到旧值(0), 导致 store 写错数据。
// master 在 wready=1 期间保证 wdata 稳定, 故提交时直接用 wdata 即可。

// 写提交: 直接用当拍 wdata
if (aw_recv && wvalid && wready)
begin
  dpic_mem_write({32'b0, aw_addr_latch}, wdata, {4'b0, w_mask_latch});
  bvalid  <= 1'b1;
  aw_recv <= 1'b0;
end
```

**为什么正确**：AXI 协议规定 master 在 `wvalid && wready` 期间 `wdata` 稳定，slave 当拍取 `wdata` 即可，无需也不应该用上一拍锁存的旧值。

---

### 3.7 `vsrc/core.v` —— 修正 `pmem_sel` 段判断，覆盖全 128MB（含栈区）

**改动要点**：原判断 `lsu_araddr[31:24] == 8'h80` 只覆盖 16MB（`0x80000000~0x80FFFFFF`），**漏掉栈区 `0x81~0x87`**。

**原 bug（错误写法）**：

```verilog
wire pmem_sel = (lsu_araddr[31:24] == 8'h80);  // 仅 16MB
```

栈区在 `0x87xxxxxx`，漏判后栈区 store/load 全丢失 → DUT 栈内存恒 0，与 REF 比对必 mismatch。

**修复（第 256-270 行）**：

```verilog
// pmem 段 = 0x80000000~0x87FFFFFF (128MB, 与 NEMU CONFIG_MBASE/CONFIG_MSIZE 一致),
// 故段判断须覆盖 0x80~0x87 全部, 不能只取 ==0x80(仅 16MB)。栈区在 0x87xxxxxx,
// 若漏判则栈区 store/load 全丢失 -> DUT 栈内存恒 0, 与 REF 比对必 mismatch。
// mmio(uart/rtc) 在 0xa00000xx, 不在此范围, 由 uart_sel/rtc_sel 单独路由。
wire pmem_sel = (lsu_araddr[31:24] >= 8'h80) && (lsu_araddr[31:24] <= 8'h87);
dpic_mem u_dmem (
  .araddr(lsu_araddr), .arvalid(lsu_arvalid && pmem_sel), .arready(dmem_arready),
  .awaddr(lsu_awaddr), .awvalid(lsu_awvalid && pmem_sel), .awready(dmem_awready),
  .wdata(lsu_wdata), .wmask(lsu_wmask), .wvalid(lsu_wvalid && pmem_sel), .wready(dmem_wready),
  // ...
);
```

`arvalid`/`awvalid`/`wvalid` 全部 `&& pmem_sel`，覆盖 `0x80~0x87` 全段；`uart/rtc` 在 `0xa00000xx`，不在此范围，由 `uart_sel`/`rtc_sel` 单独路由，互不冲突。

---

## 4. 调试中发现的 3 个 bug（均已修复）

| # | 现象 | 根因 | 修复位置 |
|---|---|---|---|
| 1 | DIFFTEST MISMATCH（x1 DUT=0, REF=0x80000fc8） | `core.v` 段判断只覆盖 16MB，栈区 `0x87` 漏判 | `core.v` 改 `pmem_sel` 覆盖 `0x80~0x87` |
| 2 | 关 difftest 跑 DUT 内存全 0 / `load_image_bin` 未声明 | `load_image_bin` 锁在 `#if ENABLE_DIFFTEST` 内 + `monitor.c` 不调 | `difftest.cpp` 移出 `#if`；`monitor.c` 无条件调 |
| 3 | 纯 DUT 跑在 pc=0 BAD TRAP（返回地址栈槽被写 0） | `dpic_mem.v` 写提交用延迟一拍的 `w_data_latch` 旧值（0） | `dpic_mem.v` 改用当拍 `wdata` 直接提交 |

此外构建期还修过：`dpic_mem.cpp` 缺 `#include <cstdlib>`（`strtoul` 未声明）。

---

## 5. 最终验证

- 配置：`auto.conf` 中 `CONFIG_DPI_MEM=y` + `CONFIG_DIFFTEST=y`。
- 结果：amtest **HIT GOOD TRAP**，`pc=0x800010d0`，`total_inst=1915`，与改造前结果一致。
- 调试打印已全部移除，`auto.conf` 恢复 `CONFIG_DIFFTEST=y`。

---

## 6. 改造后数据链路（一句话总结）

```
取指/访存 → dpic_mem.v
            ├─ 读: dpic_mem_read  → pmem_words[] (DUT 真相)
            └─ 写: dpic_mem_write → pmem_words[] (DUT 真相)
                         │
          difftest 开启时(仅初始化一次):
            dpi_pmem_copy_out → ref_difftest_memcpy(TO_REF) → NEMU pmem (REF 真相)
```
