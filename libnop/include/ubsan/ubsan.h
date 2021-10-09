#ifndef __UBSAN_H__
#define __UBSAN_H__

#include <nop/type.h>

typedef struct ub_location_t ub_location_t;
typedef struct ub_type_t ub_type_t;

typedef struct ub_overflow_t ub_overflow_t;
typedef struct ub_bounds_t ub_bounds_t;
typedef struct ub_mismatch_t ub_mismatch_t;
typedef struct ub_vla_t ub_vla_t;

struct ub_location_t {
  const char *path;
  uint32_t line;
  uint32_t column;
};

struct ub_type_t {
  uint16_t type;
  uint16_t info;

  char name[];
};

struct ub_overflow_t {
  ub_location_t location;
  const ub_type_t *type;
};

struct ub_bounds_t {
  ub_location_t location;
  ub_type_t *left;
  ub_type_t *right;
};

struct ub_mismatch_t {
  ub_location_t location;
  ub_type_t *type;
  uint8_t align;
  uint8_t kind;
};

struct ub_vla_t {
  ub_location_t location;
  ub_type_t *type;
};

void __ubsan_handle_add_overflow(ub_overflow_t *data);
void __ubsan_handle_sub_overflow(ub_overflow_t *data);
void __ubsan_handle_mul_overflow(ub_overflow_t *data);
void __ubsan_handle_divrem_overflow(ub_overflow_t *data);
void __ubsan_handle_negate_overflow(ub_overflow_t *data);
void __ubsan_handle_pointer_overflow(ub_overflow_t *data);

void __ubsan_handle_shift_out_of_bounds(ub_bounds_t *data);
void __ubsan_handle_out_of_bounds(ub_bounds_t *data);

void __ubsan_handle_type_mismatch_v1(ub_mismatch_t *data, void *ptr);

void __ubsan_handle_vla_bound_not_positive(ub_vla_t *data);

#endif
