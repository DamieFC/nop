ENTRY(nop)

SECTIONS {
  . = 0x00010000;

  .entry : {
    *(.entry*)
  }

  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
    
    *(COMMON)
    *(.bss*)
  }
}
