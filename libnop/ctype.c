#include <ctype.h>

int isspace(int chr) {
  return (chr == ' ' || chr == '\n' || chr == '\t');
}

int toupper(int chr) {
  if (chr >= 'a' && chr <= 'z') {
    return (chr - 'a') + 'A';
  }
  
  return chr;
}
