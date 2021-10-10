#include <nop/dbg.h>
#include <stdio.h>

int main(int argc, const char **argv) {
  printf("Hello, world!\n");
  dbg_panic("test!");
  
  return 0;
}
