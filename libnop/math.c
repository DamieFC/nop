#include <nop/type.h>
#include <math.h>

int abs(int x) {
  return ((x < 0) ? -x : x);
}

long labs(long x) {
  return ((x < 0) ? -x : x);
}

long long llabs(long long x) {
  return ((x < 0) ? -x : x);
}

// cringe
int64_t __divdi3(int64_t x, int64_t y) {
  return (int64_t)((int)(x) / (int)(y));
}
