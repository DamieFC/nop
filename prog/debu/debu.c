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
    printf("Exception %d: ", data_2);
    
    switch (data_2) {
      
    }
  }
  
  return 0;
}
