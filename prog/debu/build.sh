#!/usr/bin/sh

clang -Os --target=i586-unknown-elf -march=i586 -fsanitize=undefined,unsigned-integer-overflow,local-bounds -ffreestanding -fno-builtin -nostdlib -I include -I ../../libnop/include $(find . -name "*.c") -c
find . -name "*.asm" -exec nasm -O4 -felf {} \;

i586-elf-ld -T link_bin.ld -nostdlib $(find . -name "*.o") $(find ../../libnop -name "*.o") -o debu.nex
i586-elf-ld -T link_elf.ld -nostdlib $(find . -name "*.o") $(find ../../libnop -name "*.o") -o debu.elf
