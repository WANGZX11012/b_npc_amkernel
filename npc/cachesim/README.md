# cachesim — NPC ICACHE 行为模型

模拟 NPC 的 ICACHE，对同一份 PC trace 统计 miss 次数，用于验证 RTL 实现。

- 模型：直接映射（ways=1）、只读、按块统计（一次块填充 = 1 次 miss）
- 参数同源：默认 `blk`/`blocks` 读 `include/generated/autoconf.h`

## 前提条件

1. 已跑过 `make menuconfig`（生成 `include/generated/autoconf.h`）
2. `CONFIG_ITRACE=y`
3. 有 trace 文件：`npc/build/itrace.bin`（每次 `make run` 重新生成并覆盖）
   - 格式：连续 `uint32` PC，每个退休指令一条，小端，无文件头

## 编译与运行

在 `npc/cachesim/` 下：

| 命令 | 作用 |
|---|---|
| `make` | 编译，产出 `./cachesim` |
| `make run` | 用默认参数跑（trace 默认 `../build/itrace.bin`） |
| `make run ARGS="16 1024"` | 自定义块大小/块数 |
| `make run TRACE=/tmp/x.bin` | 换 trace |
| `make sweep` | 参数矩阵扫描（20 组） |
| `make clean` | 删除产物 |

直接调用：./cachesim # 默认 = autoconf 配置 ./cachesim 16 # 块大小(字节) ./cachesim 16 1024 # 块大小 + 块数 ./cachesim --sweep # 扫描模式

## 工具用于和npc交叉验证

