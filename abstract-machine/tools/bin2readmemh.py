#!/usr/bin/env python3
# 把 AM 编出的 .bin 转成 Verilog $readmemh 兼容的 hex 格式
# 格式：@<起始地址(十六进制)>  然后每行一个 32-bit word（十六进制，无前缀）
# 用法：bin2readmemh.py <input.bin> [output.hex]

import sys

def main():
    if len(sys.argv) < 2:
        sys.exit("Usage: bin2readmemh.py <input.bin> [output.hex]")
    bin_path = sys.argv[1]
    out_path = sys.argv[2] if len(sys.argv) > 2 else bin_path + '-readmemh'

    with open(bin_path, 'rb') as fbin, open(out_path, 'w') as fout:
        fout.write('@00000000\n')
        while True:
            word = fbin.read(4)
            if not word:
                break
            # 不足 4 字节补 0（小端）
            val = int.from_bytes(word.ljust(4, b'\x00'), 'little')
            fout.write('%08x\n' % val)

if __name__ == '__main__':
    main()
