#ifndef __STDIO_H__
#define __STDIO_H__

#include <nop/type.h>
#include <stdarg.h>

#define STDIO_FILE_MAX 16

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define stdin  (stdio_files + 0)
#define stdout (stdio_files + 1)
#define stderr (stdio_files + 2)

#define putc(chr, file) (fputc(chr, file))

#define fputs(str, file) (fputs_opt(str, file, 0, 0, ' '))
#define fputn(num, base, upper, file) (fputn_opt(num, base, upper, file, 0, 0, ' '))

#define putchar(chr) (fputc(chr, stdout))
#define puts(str) (fputs(str, stdout))
#define putn(num, base, upper) (fputn(num, base, upper, stdout))

#define rewind(file) (fseek(file, 0, SEEK_SET))

#define printf(...) (fprintf(stdout, __VA_ARGS__))

#define EOF (-1)

typedef struct FILE FILE;

struct FILE {
  int prog; // 0=file, 1=prog
  int free;
  
  int id;
};

extern FILE stdio_files[];

void stdio_init(int prog_in, int prog_out);

int fputc(int chr, FILE *file);

int fputs_opt(const char *str, FILE *file, int pad_aln, int pad_len, char pad_chr);
int fputn_opt(int num, int base, int upper, FILE *file, int pad_aln, int pad_len, char pad_chr);

int vfprintf(FILE *file, const char *format, va_list args);
int fprintf(FILE *file, const char *format, ...);
int snprintf(char *buffer, size_t size, const char *format, ...);

FILE *fopen(const char *path, const char *mode);
int   fclose(FILE *file);
int   fflush(FILE *file);

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *file);
size_t fread(void *buffer, size_t size, size_t count, FILE *file);

int     fseek(FILE *file, ssize_t offset, int mode);
ssize_t ftell(FILE *file);

int remove(const char *path);
int rename(const char *path, const char *new_path);

#endif
