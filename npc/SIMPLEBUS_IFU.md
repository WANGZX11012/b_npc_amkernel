# SimpleBus IFU 实现记录

## 改了什么

### 目标

IFU 通过 SimpleBus 协议访问指令内存，ctrl 不再硬编码取指延迟。

### 改前 vs 改后

| | 改前 | 改后 |
|------|------|------|
| 取指延迟 | ctrl 里硬编码 FET_IDLE→FET_WAIT 两拍 | IFU 自己管理 idle→wait，ctrl 等 `ifu_done` |
| 内存接口 | `addr`→`inst`（固定 1 拍组合/同步读） | `reqValid`/`addr`→`respValid`/`rdata`（SimpleBus） |
| IFU 职责 | 只管 PC | PC + 总线事务管理 |
| 延迟可变 | 不支持 | 支持（改 IFU 等待条件即可，ctrl 不用动） |

### 改动清单

| 文件 | 改动 |
|------|------|
| `vsrc/IFU.v` | 加 2 状态 bus FSM（idle/wait）+ `ifu_raddr/reqValid/rdata/respValid/done` |
| `vsrc/inst_mem.v` | 接口改为 SimpleBus 从设备：`reqValid`→`respValid+rdata`（1 拍后拉高） |
| `vsrc/ctrl.v` | FET_IDLE/FET_WAIT→单 FETCH 状态，`ifu_done` 控制转移 |
| `vsrc/npc_defs.vh` | 状态宏恢复 6 状态（去 FET_IDLE/FET_WAIT） |
| `vsrc/core.v` | 连线 IFU↔inst_mem 的 SimpleBus 信号，`IR` 从 `ifu_rdata` 锁存 |

### SimpleBus 信号

```
IFU (主设备)                  inst_mem (从设备)
──────────                    ────────
ifu_raddr[31:0]  ──────────→  addr
ifu_reqValid     ──────────→  reqValid
ifu_rdata[31:0]  ←──────────  rdata
ifu_respValid    ←──────────  respValid
ifu_done         (输出给 ctrl：本拍指令有效)
```

### 时序

```
idle:  ifu_reqValid=1, ifu_raddr=pc  →  内存收到请求
wait:  ifu_respValid=1 → ifu_rdata 有效 → ifu_done=1 → ctrl 进 DEC
```

### FSM

```
IFU bus:     idle ──→ wait ──→ idle ──→ ...
                ↑respValid=1
Ctrl:   FETCH ──→ FETCH ──→ DEC ──→ ...
            ↑ifu_done=0  ↑ifu_done=1
```
