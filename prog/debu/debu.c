#include <arch/i586.h>
#include <nop/send.h>
#include <nop/type.h>
#include <nop/dbg.h>
#include <string.h>
#include <stdio.h>

__attribute__((__section__(".entry"), __used__))
int nex_start(int id, uint32_t type, uint32_t data_1, uint32_t data_2, uint32_t data_3) {
  if (type == nop_type("INIT")) {
    if (!nop_send(0, "HOOK", 0x31, 0, 0)) {
      dbg_init(0x03F8);
      
      dbg_failf("debu: cannot hook up kernel panic handler\n");
      for (;;);
    }
    
    for (int i = 0; i < 32; i++) {
      if (!nop_send(0, "HOOK", i, 0, 0)) {
        dbg_init(0x03F8);
        
        dbg_failf("debu: cannot hook up handler %d\n", i);
        dbg_panic("cannot hook up handler");
      }
    }
  } else if (type == nop_type("TRIG")) {
    int term = nop_find("TERM");
    if (!term) return 0;
    
    stdio_init(term, term);
    i586_regs_t *regs = (void *)(data_1);
    
    if (data_2 == 0x31) {
      printf("\x1B[4m\x1B[92mDEBU.NEX: \x1B[96mkernel panic\x1B[m\n");
      
      if (data_3) {
        printf("called by: \x1B[96mprogram %d\x1B[m\n", data_3);
      } else {
        printf("called by: \x1B[96mkernel\x1B[m\n");
      }
      
      printf("reason: \x1B[96m%s\x1B[m\n\n", nop_phys(data_3, regs->edi));
    } else {
      printf("\x1B[92mDEBU.NEX: \x1B[96mCPU exception detected\x1B[m\n");
      printf("exception: \x1B[96m%d\x1B[m\n", data_2);
      printf("reason: \x1B[96m");
      
      switch (data_2) {
        case 0:
          printf("divide by zero\x1B[m\n\n");
          break;
        
        case 1:
          printf("debug\x1B[m\n\n");
          break;
          
        case 2:
          printf("non-maskable interrupt\x1B[m\n\n");
          break;
          
        case 3:
          printf("breakpoint\x1B[m\n\n");
          break;
          
        case 4:
          printf("overflow\x1B[m\n\n");
          break;
        
        case 5:
          printf("bound range exceeded\x1B[m\n\n");
          break;
          
        case 6:
          printf("invalid opcode\x1B[m\n\n");
          break;
          
        case 7:
          printf("device not available\x1B[m\n\n");
          break;
          
        case 8:
          printf("double fault\x1B[m\n\n");
          break;
          
        case 9:
          printf("coprocessor segment overrun\x1B[m\n\n");
          break;
          
        case 10:
          printf("invalid TSS\x1B[m\n\n");
          break;
          
        case 11:
          printf("segment not present\x1B[m\n\n");
          break;
          
        case 12:
          printf("stack segment fault\x1B[m\n\n");
          break;
          
        case 13:
          printf("general protection fault\x1B[m\n\n");
          break;
          
        case 14:
          printf("page fault\x1B[m\n\n");
          break;
          
        default:
          printf("reserved\x1B[m\n\n");
          break;
      }
    }
    
    printf("\x1B[95meax:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95mebx:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95mecx:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95medx:\x1B[90m \x1B[93m0x%08X\x1B[90m\n",
           regs->eax, regs->ebx, regs->ecx, regs->edx);
    printf("\x1B[95mesi:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95medi:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95mebp:\x1B[90m \x1B[93m0x%08X\x1B[90m, \x1B[95mesp:\x1B[90m \x1B[93m0x%08X\x1B[90m\n",
           regs->esi, regs->edi, regs->ebp, regs->esp);
    printf("\x1B[95meip:\x1B[90m \x1B[93m0x%08X\x1B[90m\n\n",
           regs->eip);
    
    int prog_len = 0;
    int *prog_arr = (void *)(nop_send(0, "STAC", (uint32_t)(&prog_len), 0, 0));
    
    int prog_pos = prog_len - 2; // exclude DEBU
    int is_prog = 0;
    
    printf("\x1B[mstack trace:\n");
    uint32_t *stack = (void *)(regs->ebp);
    
    for (int i = 0; i < 32; i++) {
      if (!stack) break;
      
      uint32_t phys = (uint32_t)(nop_phys(data_3, stack[1]));
      
      if (phys != stack[1]) {
        char name[5] = {0};
        size_t size = 0;
        
        nop_send(0, "LIST", prog_arr[prog_pos], (uint32_t)(name), (uint32_t)(&size));
        
        printf("\x1B[90m- \x1B[93m0x%08X\x1B[90m -> \x1B[93m0x%08X\x1B[90m(\x1B[92m\"%s\"\x1B[90m, \x1B[35m%d bytes\x1B[90m)\n", stack[1], phys, name, size);
        is_prog = 1;
      } else {
        printf("\x1B[90m- \x1B[93m0x%08X\x1B[90m\n", stack[1]);
        
        if (is_prog) {
          prog_pos--;
          is_prog = 0;
        }
      }
      
      stack = (void *)(stack[0]);
    }
    
    printf("\n\x1B[mprogram stack:\n");
    
    for (int i = prog_len - 1; i >= 0; i--) {
      char name[5] = {0};
      size_t size = 0;
      
      nop_send(0, "LIST", prog_arr[i], (uint32_t)(name), (uint32_t)(&size));
      printf("\x1B[90m- \x1B[m%d\x1B[90m(\x1B[92m\"%s\"\x1B[90m, \x1B[35m%d bytes\x1B[90m)\n", prog_arr[i], name, size);
    }
  }
  
  return 0;
}
