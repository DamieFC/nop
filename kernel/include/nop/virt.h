#ifndef __NOP_VIRT_H__
#define __NOP_VIRT_H__

#include <nop/type.h>

#define VIRT_USER    (1 << 2)
#define VIRT_WRITE   (1 << 1)
#define VIRT_PRESENT (1 << 0)

#define VIRT_NOP_ADDR 0x00000000
#define VIRT_NOP_SIZE 0x00100000
#define VIRT_NOP_PROG 0xC0000000

extern uint32_t *virt_table;

void virt_init(void);

uint32_t *virt_alloc(void);
void      virt_free(uint32_t *table);
void      virt_load(uint32_t *table);

void virt_map(uint32_t *table, void *phys_addr, void *virt_addr, uint32_t flags, size_t count);
void virt_unmap(uint32_t *table, void *virt_addr, size_t count);

#endif
