#ifndef __NOP_SYST_H__
#define __NOP_SYST_H__

#include <arch/i586.h>
#include <nop/type.h>

#define SYST_OPEN_MAX 32

// seek modes
#define SYST_SEEK_ZERO 0
#define SYST_SEEK_OFFS 1
#define SYST_SEEK_SIZE 2

// stat bitfields
#define SYST_RO (1 << 0) // read only
#define SYST_HD (1 << 1) // hidden
#define SYST_SY (1 << 2) // system
#define SYST_DR (1 << 4) // directory

// syst subsyscalls
#define SYST_LOAD 0x44414F4C
#define SYST_KILL 0x4C4C494B
#define SYST_PAUS 0x53554150
#define SYST_LIST 0x5453494C
#define SYST_TIME 0x454D4954
#define SYST_REQU 0x55514552
#define SYST_FREE 0x45455246
#define SYST_OPEN 0x4E45504F
#define SYST_CLOS 0x534F4C43
#define SYST_READ 0x44414552
#define SYST_WRIT 0x54495257
#define SYST_SEEK 0x4B454553
#define SYST_TELL 0x4C4C4554
#define SYST_STAT 0x54415453
#define SYST_SIZE 0x455A4953
#define SYST_DELE 0x454C4544

#include <nop/type.h>
#include <nop/fat.h>

typedef struct syst_file_t syst_file_t;

struct syst_file_t {
  char path[FAT_PATH_MAX];
  int free, stat;
  
  void *buffer;
  size_t size, offset;
};

extern syst_file_t *syst_files;
extern size_t syst_index;

void syst_init(void);
void syst_call(i586_regs_t *regs, idt_hand_t *hand);

int    syst_load(const char *path);
void   syst_kill(int id);
void   syst_paus(int id, int pause); // disables message receiving
int    syst_list(void); // returns file descriptor with list of programs
void   syst_time(int id, int enable); // enables message every tick(TICK)
int    syst_requ(void *ptr); // requests a 4 KiB page...
void   syst_free(void *ptr); // ...and frees it
int    syst_open(const char *path);
void   syst_clos(int id);
size_t syst_read(int id, void *buffer, size_t size);
size_t syst_writ(int id, void *buffer, size_t size);
void   syst_seek(int id, size_t offset, int mode);
size_t syst_tell(int id);
int    syst_stat(int id, int new_stat); // will only be set if != -1, otherwise just return stat
void   syst_size(int id, size_t size); // resizes file(increase or decrease)
void   syst_dele(const char *path);

#endif
