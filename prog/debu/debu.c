#include <arch/i586.h>
#include <nop/send.h>
#include <nop/type.h>
#include <nop/dbg.h>
#include <string.h>
#include <stdio.h>

__attribute__((__section__(".entry"), __used__))
int nex_start(int id, uint32_t type, uint32_t data_1, uint32_t data_2, uint32_t data_3) {
  if (type == nop_type("INIT")) {
    for (int i = 0; i < 16; i++) {
      if (!nop_send(0, "HOOK", i, 0, 0)) {
        dbg_init(0x03F8);
        
        dbg_failf("debu: cannot hook up handler %d\n", i);
        dbg_panic();
      }
    }
  } else if (type == nop_type("TRIG")) {
    int term = nop_find("TERM");
    if (!term) return 0;
    
    stdio_init(term, term);
    
    printf("oh no, DEBU.NEX detected a CPU exception!\n");
    printf("exception %d: ", data_2);
    
    switch (data_2) {
      case 0:
        printf("divide by zero\n\n");
        break;
      
      case 1:
        printf("debug\n\n");
        break;
        
      case 2:
        printf("non-maskable interrupt\n\n");
        break;
        
      case 3:
        printf("breakpoint\n\n");
        break;
        
      case 4:
        printf("overflow\n\n");
        break;
      
      case 5:
        printf("bound range exceeded\n\n");
        break;
        
      case 6:
        printf("invalid opcode\n\n");
        break;
        
      case 7:
        printf("device not available\n\n");
        break;
        
      case 8:
        printf("double fault\n\n");
        break;
        
      case 9:
        printf("coprocessor segment overrun\n\n");
        break;
        
      case 10:
        printf("invalid TSS\n\n");
        break;
        
      case 11:
        printf("segment not present\n\n");
        break;
        
      case 12:
        printf("stack segment fault\n\n");
        break;
        
      case 13:
        printf("general protection fault\n\n");
        break;
        
      case 14:
        printf("page fault\n\n");
        break;
        
      case 15:
        printf("reserved\n\n");
        break;
    }
    
    i586_regs_t *regs = (void *)(data_1);
    
    printf("eax: 0x%08X, ebx: 0x%08X, ecx: 0x%08X, edx: 0x%08X\n", regs->eax, regs->ebx, regs->ecx, regs->edx);
    printf("esi: 0x%08X, edi: 0x%08X, ebp: 0x%08X, esp: 0x%08X\n", regs->esi, regs->edi, regs->ebp, regs->esp);
    printf("eip: 0x%08X\n\n", regs->eip);
    
    printf("stack trace:\n");
    uint32_t *stack = (void *)(regs->ebp);
    
    for (int i = 0; i < 32; i++) {
      if (!stack) break;
      
      uint32_t phys = (uint32_t)(nop_phys(data_3, stack[1]));
      
      if (phys != stack[1]) {
        char name[5] = {0};
        size_t size = 0;
        
        nop_send(0, "LIST", data_3, (uint32_t)(name), (uint32_t)(&size));
        
        printf("- 0x%08X -> 0x%08X(\"%s\", %d bytes)\n", stack[1], phys, name, size);
      } else {
        printf("- 0x%08X\n", stack[1]);
      }
      
      stack = (void *)(stack[0]);
    }
  }
  
  return 0;
}
