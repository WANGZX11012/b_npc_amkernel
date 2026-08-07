# NPC AXI4-Lite 总线概览

## 一、架构

NPC 有两个独立的 AXI4-Lite 主设备，分别对接各自的从设备，两条总线物理独立、无仲裁：

```
  ctrl.v ──┬──► IFU ──[axi_lite_master]──► inst_mem  (只读)
           └──► LSU ──[axi_lite_master]──► data_mem  (读写)
```

- IFU/LSU 各自实例化同一个共享模块 `axi_lite_master`，把"简单请求"翻译成 AXI4-Lite 五通道握手。
- ctrl 不直接碰 AXI 信号，只通过 `fetch_req` / `mem_req` 发请求、用 `done` 收完成。

## 二、模块职责

| 模块 | 职责 |
|---|---|
| [axi_lite_master.v](vsrc/axi_lite_master.v) | 共享主设备核：6 状态 FSM（IDLE/AR/R/AW/W/B），把 req 翻译成 5 通道握手 |
| [IFU.v](vsrc/IFU.v) | 取指：`req_we=0`，只用 AR+R 通道，AW/W/B 悬空 |
| [LSU.v](vsrc/LSU.v) | 访存：5 通道全用，额外负责 wmask 生成、wdata 摆位、load 选字节+符号扩展 |
| [inst_mem.v](vsrc/inst_mem.v) | 指令从设备：无 FSM，1 拍返回，仅 AR+R |
| [data_mem.v](vsrc/data_mem.v) | 数据从设备：3 状态 FSM + `aw_recv` 粘合位 + DELAY 计数器 |

## 三、master FSM

```
读:  IDLE → AR → R → IDLE          (req_we=0)
写:  IDLE → AW → W → B → IDLE      (req_we=1)
```

- VALID 信号只看 state 寄存器，不依赖 READY，握手前不拉低（满足 AXI 规范）。
- `stall`（LFSR 随机停顿）只 gate READY 和 done，不 gate VALID。
- `done` 在 R 或 B 通道握手拍拉高 1 拍，ctrl 据此推进。

## 四、IFU ↔ inst_mem（只读取指）

- IFU 在 [IFU.v:55](vsrc/IFU.v#L55) 实例化 master，`req_we=1'b0`，写通道输出悬空、输入接 0。
- inst_mem 在 [inst_mem.v:20](vsrc/inst_mem.v#L20) 永远 `arready=1`；AR 握手拍锁数据并拉 `rvalid`，R 握手后清。
- 无延迟，取指共 3 拍：AR 握手 → R 握手 → ctrl 进 DEC。

## 五、LSU ↔ data_mem（读写访存）

### LSU 特有逻辑（master 不懂的事）

1. **wmask 生成**（[LSU.v:69](vsrc/LSU.v#L69)）：`mem_width`（BYTE/HALF/WORD）+ `addr[1:0]` → 4 位字节掩码。
2. **wdata 摆位**（[LSU.v:81](vsrc/LSU.v#L81)）：store 数据复制到各字节通道，由 wmask 决定实际写入哪个位置。
3. **load 选字节**（[LSU.v:111](vsrc/LSU.v#L111)）：data_mem 返回整 word，LSU 按 `addr[1:0]` 右移选目标字节/半字，再按 `mem_signed` 符号或零扩展。

### data_mem 的写事务处理

AXI 把写地址（AW）和写数据（W）分两通道。data_mem 用 `aw_recv` 标志位粘合：
- AW 握手拍：锁存 `aw_word_lat`，置 `aw_recv=1`，`wready` 跟着拉高。
- W 握手拍：用锁存地址 + wdata + wmask 执行写，清 `aw_recv`，进 DELAY 计数。

### 时序（DELAY=1，无 stall）

| 事务 | 拍数 | 流程 |
|---|---|---|
| 读 | 4 拍 | AR 握手 → S_RD 数 1 拍 → rvalid 下拍可见 → R 握手 |
| 写 | 5 拍 | AW 握手 → W 握手并写 mem → S_WR 数 1 拍 → bvalid 下拍可见 → B 握手 |

## 六、握手约束合规性

| 约束 | 实现 |
|---|---|
| VALID 不依赖 READY | master 的三个 VALID 只看 state 寄存器 |
| VALID 握手前不拉低 | state 在握手前不自退，slave 的 rvalid/bvalid 保持到握手 |
| READY 不引起死锁 | `stall` 只 gate READY，统计上必然结束 |
| payload 握手前稳定 | araddr/awaddr/wdata/wmask 均来自寄存器 |

## 七、两个 master 对比

| | IFU + inst_mem | LSU + data_mem |
|---|---|---|
| 通道数 | 2（AR+R） | 5（AR+R+AW+W+B） |
| slave 复杂度 | 无 FSM，1 拍 | 3 状态 FSM + aw_recv + DELAY |
| 特有逻辑 | 无 | wmask/wdata/load 处理 |
| 拍数（DELAY=1） | 3 拍 | 读 4 / 写 5 |
| 共享模块 | axi_lite_master | axi_lite_master（同一份） |

核心设计：`axi_lite_master` 是抽出来的共享主设备核，IFU/LSU 只负责"喂请求 + 用 done"，不重复写握手 FSM。
