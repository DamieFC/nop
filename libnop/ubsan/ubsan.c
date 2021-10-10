#include <ubsan/ubsan.h>
#include <nop/dbg.h>

void __ubsan_handle_add_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: add overflow\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan add overflow");
}

void __ubsan_handle_sub_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: sub overflow\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan sub overflow");
}

void __ubsan_handle_mul_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: mul overflow\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan mul overflow");
}

void __ubsan_handle_divrem_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: divrem overflow\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan divrem overflow");
}

void __ubsan_handle_negate_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: negate overflow\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan negate overflow");
}

void __ubsan_handle_pointer_overflow(ub_overflow_t *data) {
  dbg_failf("ubsan: pointer overflow\n");
  
  if (data) {
    dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
    dbg_infof("- type: %s\n", data->type->name);
  }
  
  dbg_panic("ubsan pointer overflow");
}

void __ubsan_handle_shift_out_of_bounds(ub_bounds_t *data) {
  dbg_failf("ubsan: shift out of bounds\n");
  dbg_infof("- file:  %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- left:  %s\n", data->left->name);
  dbg_infof("- right: %s\n", data->right->name);
  
  dbg_panic("ubsan shift out of bounds");
}

void __ubsan_handle_out_of_bounds(ub_bounds_t *data) {
  dbg_failf("ubsan: array out of bounds\n");
  dbg_infof("- file:  %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- array: %s\n", data->left->name);
  dbg_infof("- index: %s\n", data->right->name);
  
  dbg_panic("ubsan array out of bounds");
}

void __ubsan_handle_type_mismatch_v1(ub_mismatch_t *data, void *ptr) {
  if (ptr) {
    if ((uint32_t)(ptr) & ((1 << data->align) - 1)) {
      dbg_failf("ubsan: misaligned pointer(0x%08X)\n", ptr);
    } else {
      dbg_failf("ubsan: no space for object(0x%08X)\n", ptr);
    }
  } else {
    dbg_failf("ubsan: use of NULL pointer\n");
  }
  
  dbg_infof("- file:  %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type:  %s\n", data->type->name);
  dbg_infof("- align: %d\n", data->align);
  
  dbg_panic("ubsan type mismatch");
}

void __ubsan_handle_vla_bound_not_positive(ub_vla_t *data) {
  dbg_failf("ubsan: array of negative size\n");
  dbg_infof("- file: %s at %d:%d\n", data->location.path, data->location.line, data->location.column);
  dbg_infof("- type: %s\n", data->type->name);
  
  dbg_panic("ubsan array of negative size");
}

void __ubsan_handle_nonnull_arg() {
  dbg_failf("ubsan: passed NULL argument\n");
  dbg_panic("ubsan passed NULL argument");
}
