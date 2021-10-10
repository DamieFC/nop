#include <stdio.h>

#define ANSI_RESET     "\x1B[m"
#define ANSI_UNDERLINE "\x1B[4m"
#define ANSI_REVERSE   "\x1B[7m"

int main(int argc, const char **argv) {
  printf(ANSI_RESET "attributes:\n- default\n");
  
  printf(ANSI_RESET "- " ANSI_UNDERLINE "underline\n");
  printf(ANSI_RESET "- " ANSI_REVERSE "reverse\n");
  printf(ANSI_RESET "- " ANSI_UNDERLINE ANSI_REVERSE "underline reverse\n\n");
  
  printf(ANSI_RESET "colors:\n");
  
  for (int i = 0; i < 16; i++) {
    printf("\x1B[%dm", i >= 8 ? (i + 92) : (i + 40));
    
    for (int j = 0; j < 16; j++) {
      printf("\x1B[%dm Aa ", j >= 8 ? (j + 82) : (j + 30));
    }
    
    printf("\n");
  }
  
  printf(ANSI_RESET);
  return 0;
}
