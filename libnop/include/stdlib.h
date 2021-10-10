#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <nop/type.h>
#include <math.h>

typedef struct mem_node_t mem_node_t;

struct mem_node_t {
  uint32_t size: 31;
  uint8_t  free: 1;
} __attribute__((packed));

extern void *mem_heap;
extern size_t mem_size;
extern size_t mem_used;

void mem_init(size_t size);
void mem_defrag(void);

void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void *realloc(void *ptr, size_t new_size);

void free(void *ptr);

int atoi(const char *str);

int system(const char *cmd);
void exit(int value);

#endif
