#!/usr/bin/sh

clang -Os -g --target=i586-unknown-elf -march=i586 -fsanitize=undefined,unsigned-integer-overflow,local-bounds -ffreestanding -fno-builtin -nostdlib -I include $(find . -name "*.c") -c
find . -name "*.asm" -exec nasm -O4 -felf {} \;

i586-elf-ld -T link_bin.ld -nostdlib $(find . -name "*.o") -o nopkernl.bin
i586-elf-ld -T link_elf.ld -nostdlib $(find . -name "*.o") -o nopkernl.elf
