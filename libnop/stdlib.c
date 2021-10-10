#include <nop/send.h>
#include <nop/type.h>
#include <nop/dbg.h>
#include <stdlib.h>
#include <string.h>

void *mem_heap = NULL;
size_t mem_size = 0;
size_t mem_used = 0;

void mem_init(size_t size) {
  if ((mem_heap = (void *)(nop_send(0, "REQU", (size + 0x0FFF) >> 12, 0, 0)))) {
    mem_size = size;

    mem_node_t *node = mem_heap;
    node->size = mem_size - sizeof(mem_node_t);
    node->free = 1;
  }
}

void mem_defrag(void) {
  void *ptr = mem_heap;

  while (ptr < mem_heap + mem_size) {
    mem_node_t *node = ptr;
    mem_node_t *next_node = ptr + node->size + sizeof(mem_node_t);

    if (node->free && next_node->free) {
      node->size += next_node->size + sizeof(mem_node_t);
    } else {
      ptr = next_node;
    }
  }
}

void *malloc(size_t size) {
  void *ptr = mem_heap;
  
  while (ptr < mem_heap + mem_size) {
    mem_node_t *node = ptr;

    if (node->free) {
      if (node->size == size) {
        node->free = 0;
        mem_used += size;

        return ptr + sizeof(mem_node_t);
      } else if (node->size > size + sizeof(mem_node_t)) {
        mem_node_t *new_node = ptr + sizeof(mem_node_t) + size;

        new_node->size = node->size - (sizeof(mem_node_t) + size);
        new_node->free = 1;

        node->size = size;
        node->free = 0;

        mem_used += size;

        return ptr + sizeof(mem_node_t);
      }
    }

    ptr += node->size + sizeof(mem_node_t);
  }

  return NULL;
}

void *calloc(size_t count, size_t size) {
  void *ptr = malloc(count * size);
  memset(ptr, 0, count * size);
  
  return ptr;
}

void *realloc(void *ptr, size_t new_size) {
  if (!new_size) return NULL;

  void *new_ptr = malloc(new_size);

  if (ptr) {
    mem_node_t *node = ptr - sizeof(mem_node_t);
    size_t size = new_size < node->size ? new_size : node->size;
    
    memcpy(new_ptr, ptr, size);
    free(ptr);
  }

  return new_ptr;
}

void free(void *ptr) {
  mem_node_t *node = ptr - sizeof(mem_node_t);
  node->free = 1;

  mem_used -= node->size;
  mem_defrag();
}

int atoi(const char *str) {
  int value = 0;
  
  while (*str) {
    if (*str < '0' || *str > '9') break;
    value = (value * 10) + (*(str++) - '0');
  }
  
  return value;
}

int system(const char *cmd) {
  return 0;
}

void exit(int value) {
  dbg_panic("called exit()");
  for (;;);
}
