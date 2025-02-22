#ifndef __STRING_H__
#define __STRING_H__

#include <nop/type.h>

// TODO: fix this
#define memmove memcpy

void *memcpy(void *dest, const void *src, size_t size);
void *memset(void *ptr, int val, size_t size);
int   memcmp(const char *str_1, const char *str_2, size_t size);
void *memchr(const void *str, int val, size_t size);

size_t  strlen(const char *str);
char   *strcat(char *dest, const char *src);
char   *strncat(char *dest, const char *src, size_t size);
char   *strcpy(char *dest, const char *src);
char   *strncpy(char *dest, const char *src, size_t size);
int     strcmp(const char *str_1, const char *str_2);
int     strncmp(const char *str_1, const char *str_2, size_t size);
char   *strchr(const char *str, int val);
char   *strrchr(const char *str, int val);
char   *strstr(const char *str_1, const char *str_2);
char   *strdup(const char *str);

int strcasecmp(const char *str_1, const char *str_2);
int strncasecmp(const char *str_1, const char *str_2, size_t size);

#endif
