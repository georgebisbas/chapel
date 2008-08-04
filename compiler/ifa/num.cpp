#include <math.h>
#include <string.h>
#include <stdio.h>
#include "num.h"
#include "prim_data.h"
#include "stringutil.h"

static int 
sprint_float_val(char* str, float64 val) {
  int numchars = sprintf(str, "%g", val);
  if (strchr(str, '.') == NULL && strchr(str, 'e') == NULL) {
    strcat(str, ".0");
    return numchars + 2;
  } else {
    return numchars;
  }
}

static int 
sprint_complex_val(char* str, float64 real, float64 imm) {
  int numchars = 0;
  numchars += sprintf(str+numchars, "(");
  numchars += sprint_float_val(str+numchars, real);
  numchars += sprintf(str+numchars, ",");
  numchars += sprint_float_val(str+numchars, imm);
  numchars += sprintf(str+numchars, "i)");
  return numchars;
}

int 
sprint_imm(char *str, char *control_string, Immediate &imm) {
  int res = -1;
  switch (imm.const_kind) {
    case NUM_KIND_NONE:
      break;
    case NUM_KIND_UINT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = sprintf(str, control_string, imm.v_bool); break;
        case INT_SIZE_8: 
          res = sprintf(str, control_string, imm.v_uint8); break;
        case INT_SIZE_16:
          res = sprintf(str, control_string, imm.v_uint16); break;
        case INT_SIZE_32:
          res = sprintf(str, control_string, imm.v_uint32); break;
        case INT_SIZE_64:
          res = sprintf(str, control_string, imm.v_uint64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_INT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = sprintf(str, control_string, imm.v_bool); break;
        case INT_SIZE_8: 
          res = sprintf(str, control_string, imm.v_int8); break;
        case INT_SIZE_16:
          res = sprintf(str, control_string, imm.v_int16); break;
        case INT_SIZE_32:
          res = sprintf(str, control_string, imm.v_int32); break;
        case INT_SIZE_64:
          res = sprintf(str, control_string, imm.v_int64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_FLOAT: case NUM_KIND_IMAG:
      switch (imm.num_index) {
        case FLOAT_SIZE_32:
          res = sprintf(str, control_string, imm.v_float32); break;
        case FLOAT_SIZE_64:
          res = sprintf(str, control_string, imm.v_float64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    case NUM_KIND_COMPLEX:
      switch (imm.num_index) {
        case COMPLEX_SIZE_64:
          res = sprintf(str, control_string, 
                        imm.v_complex64.r, imm.v_complex64.i);
          break;
        case COMPLEX_SIZE_128:
          res = sprintf(str, control_string, 
                        imm.v_complex128.r, imm.v_complex128.i); 
          break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    case CONST_KIND_STRING:
      res = sprintf(str, control_string, imm.v_string);
      break;
  }
  return res;
}

int 
sprint_imm(char *str, Immediate &imm) {
  int res = -1;
  switch (imm.const_kind) {
    case NUM_KIND_NONE:
      break;
    case NUM_KIND_UINT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = sprintf(str, "%u", (unsigned)imm.v_bool); break;
        case INT_SIZE_8: 
          res = sprintf(str, "%u", (unsigned)imm.v_uint8); break;
        case INT_SIZE_16:
          res = sprintf(str, "%u", (unsigned)imm.v_uint16); break;
        case INT_SIZE_32:
          res = sprintf(str, "%u", (unsigned)imm.v_uint32); break;
        case INT_SIZE_64:
          res = sprintf(str, "%llu", imm.v_uint64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_INT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = sprintf(str, "%d", imm.v_bool); break;
        case INT_SIZE_8: 
          res = sprintf(str, "%d", imm.v_int8); break;
        case INT_SIZE_16:
          res = sprintf(str, "%d", imm.v_int16); break;
        case INT_SIZE_32:
          res = sprintf(str, "%d", imm.v_int32); break;
        case INT_SIZE_64:
          res = sprintf(str, "%lld", imm.v_int64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_FLOAT: case NUM_KIND_IMAG:
      switch (imm.num_index) {
        case FLOAT_SIZE_32:
          res = sprint_float_val(str, imm.v_float32); break;
        case FLOAT_SIZE_64:
          res = sprint_float_val(str, imm.v_float64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    case NUM_KIND_COMPLEX:
      switch (imm.num_index) {
        case COMPLEX_SIZE_64:
          res = sprint_complex_val(str,imm.v_complex64.r,imm.v_complex64.i); 
          break;
        case COMPLEX_SIZE_128:
          res = sprint_complex_val(str,imm.v_complex128.r,imm.v_complex128.i); 
          break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    case CONST_KIND_STRING:
      res = sprintf(str, "\"%s\"", imm.v_string);
      break;
  }
  return res;
}

int 
fprint_imm(FILE *fp, Immediate &imm) {
  int res = -1;
  switch (imm.const_kind) {
    case NUM_KIND_NONE:
      break;
    case NUM_KIND_UINT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = fprintf(fp, "%u", (unsigned)imm.v_bool); break;
        case INT_SIZE_8: 
          res = fprintf(fp, "%u", (unsigned)imm.v_uint8); break;
        case INT_SIZE_16:
          res = fprintf(fp, "%u", (unsigned)imm.v_uint16); break;
        case INT_SIZE_32:
          res = fprintf(fp, "%u", (unsigned)imm.v_uint32); break;
        case INT_SIZE_64:
          res = fprintf(fp, "%llu", imm.v_uint64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_INT: {
      switch (imm.num_index) {
        case INT_SIZE_1: 
          res = fprintf(fp, "%d", imm.v_bool); break;
        case INT_SIZE_8: 
          res = fprintf(fp, "%d", imm.v_int8); break;
        case INT_SIZE_16:
          res = fprintf(fp, "%d", imm.v_int16); break;
        case INT_SIZE_32:
          res = fprintf(fp, "%d", imm.v_int32); break;
        case INT_SIZE_64:
          res = fprintf(fp, "%lld", imm.v_int64); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_FLOAT: case NUM_KIND_IMAG:
      char str[80];
      switch (imm.num_index) {
        case FLOAT_SIZE_32:  
          res = sprint_float_val(str, imm.v_float32); 
          break;
        case FLOAT_SIZE_64: {
          res = sprint_float_val(str, imm.v_float64); 
          break;
        }
        default: INT_FATAL("Unhandled case in switch statement");
      }
      fputs(str, fp);
      break;
    case NUM_KIND_COMPLEX:
      switch (imm.num_index) {
        case COMPLEX_SIZE_64: {
          char str[80];
          res = sprint_complex_val(str, imm.v_complex64.r, imm.v_complex64.i); 
          fputs(str, fp);
          break;
        }
        case COMPLEX_SIZE_128: {
          char str[160];
          res = sprint_complex_val(str, 
                                   imm.v_complex128.r, imm.v_complex128.i); 
          fputs(str, fp);
          break;
        }
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    case CONST_KIND_STRING:
      res = fprintf(fp, "\"%s\"", imm.v_string);
      break;
  }
  return res;
}

void
coerce_immediate(Immediate *from, Immediate *to) {
#include "cast_code.cpp"
}

#define DO_FOLD(_op) \
      switch (imm->const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_uint8 = im1.v_uint8 _op im2.v_uint8; break; \
            case INT_SIZE_16: \
              imm->v_uint16 = im1.v_uint16 _op im2.v_uint16; break; \
            case INT_SIZE_32: \
              imm->v_uint32 = im1.v_uint32 _op im2.v_uint32; break; \
            case INT_SIZE_64: \
              imm->v_uint64 = im1.uint_value() _op im2.uint_value(); break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_int8 = im1.v_int8 _op im2.v_int8; break; \
            case INT_SIZE_16: \
              imm->v_int16 = im1.v_int16 _op im2.v_int16; break; \
            case INT_SIZE_32: \
              imm->v_int32 = im1.v_int32 _op im2.v_int32; break; \
          case INT_SIZE_64: {                                            \
              imm->v_int64 = im1.int_value() _op im2.int_value(); \
              break; \
          } \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          switch (imm->num_index) { \
            case FLOAT_SIZE_32: \
              imm->v_float32 = im1.v_float32 _op im2.v_float32; break; \
            case FLOAT_SIZE_64: \
              imm->v_float64 = im1.v_float64 _op im2.v_float64; break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
      }

#define COMPUTE_INT_POW(type, b, e)       \
  type base = b;                               \
  type exp = e;                                  \
  type res = 1;                                  \
  if (exp < 0) {                                 \
    res = 0;                                     \
  } else {                                       \
    int i;                                       \
    for (i=0; i<exp; i++) {                      \
      res *= base;                               \
    }                                            \
  }
    
#define COMPUTE_UINT_POW(type, b, e)      \
  type base = b;                     \
  type exp = e;                      \
  type res = 1;                                 \
  uint32 i;                                        \
  for (i=0; i<exp; i++) {                       \
    res *= base;                                \
  }

#define DO_FOLDPOW() \
      switch (imm->const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              {                                                         \
                COMPUTE_UINT_POW(uint8, im1.v_bool, im2.v_bool);       \
                imm->v_bool = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_8:  \
              {                                                         \
                COMPUTE_UINT_POW(uint8, im1.v_uint8, im2.v_uint8);       \
                imm->v_uint8 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_16: \
              {                                                         \
                COMPUTE_UINT_POW(uint16, im1.v_uint16, im2.v_uint16);       \
                imm->v_uint16 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_32: \
              {                                                         \
                COMPUTE_UINT_POW(uint32, im1.v_uint32, im2.v_uint32);       \
                imm->v_uint32 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_64: \
              {                                                         \
                COMPUTE_UINT_POW(uint64, im1.uint_value(), im2.uint_value()); \
                imm->v_uint64 = res;                                     \
                break;                                                  \
              }                                                         \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              {                                                         \
                COMPUTE_INT_POW(int8, im1.v_bool, im2.v_bool);       \
                imm->v_bool = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_8: \
              {                                                         \
                COMPUTE_INT_POW(int8, im1.v_int8, im2.v_int8);       \
                imm->v_int8 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_16: \
              {                                                         \
                COMPUTE_INT_POW(int16, im1.v_int16, im2.v_int16);       \
                imm->v_int16 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_32: \
              {                                                         \
                COMPUTE_INT_POW(int32, im1.v_int32, im2.v_int32);       \
                imm->v_int32 = res;                                     \
                break;                                                  \
              }                                                         \
            case INT_SIZE_64: \
              {                                                         \
                COMPUTE_INT_POW(int64, im1.int_value(), im2.int_value()); \
                imm->v_int64 = res;                                     \
                break;                                                  \
              }                                                         \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          INT_FATAL("Cannot fold ** on floating point values"); \
          break; \
      }

#define DO_FOLDB(_op) \
      switch (im1.const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (im1.num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_bool = im1.v_uint8 _op im2.v_uint8; break; \
            case INT_SIZE_16: \
              imm->v_bool = im1.v_uint16 _op im2.v_uint16; break; \
            case INT_SIZE_32: \
              imm->v_bool = im1.v_uint32 _op im2.v_uint32; break; \
            case INT_SIZE_64: \
              imm->v_bool = im1.uint_value() _op im2.uint_value(); break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (im1.num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_bool = im1.v_int8 _op im2.v_int8; break; \
            case INT_SIZE_16: \
              imm->v_bool = im1.v_int16 _op im2.v_int16; break; \
            case INT_SIZE_32: \
              imm->v_bool = im1.v_int32 _op im2.v_int32; break; \
            case INT_SIZE_64: \
              imm->v_bool = im1.int_value() _op im2.int_value(); break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          switch (im1.num_index) { \
            case FLOAT_SIZE_32: \
              imm->v_bool = im1.v_float32 _op im2.v_float32; break; \
            case FLOAT_SIZE_64: \
              imm->v_bool = im1.v_float64 _op im2.v_float64; break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
      }

#define DO_FOLDI(_op) \
      switch (imm->const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_uint8 = im1.v_uint8 _op im2.v_uint8; break; \
            case INT_SIZE_16: \
              imm->v_uint16 = im1.v_uint16 _op im2.v_uint16; break; \
            case INT_SIZE_32: \
              imm->v_uint32 = im1.v_uint32 _op im2.v_uint32; break; \
            case INT_SIZE_64: \
              imm->v_uint64 = im1.uint_value() _op im2.uint_value(); break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = im1.v_bool _op im2.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_int8 = im1.v_int8 _op im2.v_int8; break; \
            case INT_SIZE_16: \
              imm->v_int16 = im1.v_int16 _op im2.v_int16; break; \
            case INT_SIZE_32: \
              imm->v_int32 = im1.v_int32 _op im2.v_int32; break; \
            case INT_SIZE_64: \
              imm->v_int64 = im1.int_value() _op im2.int_value(); break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          switch (imm->num_index) { \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
      }

#define DO_FOLD1(_op) \
      switch (imm->const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = _op im1.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_uint8 = _op im1.v_uint8; break; \
            case INT_SIZE_16: \
              imm->v_uint16 = _op im1.v_uint16; break; \
            case INT_SIZE_32: \
              imm->v_uint32 = _op im1.v_uint32; break; \
            case INT_SIZE_64: \
              imm->v_uint64 = _op im1.v_uint64; break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = _op im1.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_int8 = _op im1.v_int8; break; \
            case INT_SIZE_16: \
              imm->v_int16 = _op im1.v_int16; break; \
            case INT_SIZE_32: \
              imm->v_int32 = _op im1.v_int32; break; \
            case INT_SIZE_64: \
              imm->v_int64 = _op im1.int_value(); break;        \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          switch (imm->num_index) { \
            case FLOAT_SIZE_32: \
              imm->v_float32 = _op im1.v_float32; break; \
            case FLOAT_SIZE_64: \
              imm->v_float64 =  _op im1.v_float64; break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
      }

#define DO_FOLD1I(_op) \
      switch (imm->const_kind) { \
        case NUM_KIND_NONE: \
          break; \
        case NUM_KIND_UINT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = _op im1.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_uint8 = _op im1.v_uint8; break; \
            case INT_SIZE_16: \
              imm->v_uint16 = _op im1.v_uint16; break; \
            case INT_SIZE_32: \
              imm->v_uint32 = _op im1.v_uint32; break; \
            case INT_SIZE_64: \
              imm->v_uint64 = _op im1.v_uint64; break; \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_INT: { \
          switch (imm->num_index) { \
            case INT_SIZE_1:  \
              imm->v_bool = _op im1.v_bool; break; \
            case INT_SIZE_8:  \
              imm->v_int8 = _op im1.v_int8; break; \
            case INT_SIZE_16: \
              imm->v_int16 = _op im1.v_int16; break; \
            case INT_SIZE_32: \
              imm->v_int32 = _op im1.v_int32; break; \
            case INT_SIZE_64: \
              imm->v_int64 = _op im1.int_value(); break;        \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
        } \
        case NUM_KIND_FLOAT: case NUM_KIND_IMAG: \
          switch (imm->num_index) { \
            default: INT_FATAL("Unhandled case in switch statement"); \
          } \
          break; \
      }

void
fold_result(Immediate *im1, Immediate *im2, Immediate *imm) {
  if (im1->const_kind == im2->const_kind) {
    if (im1->num_index > im2->num_index) {
      imm->const_kind = im1->const_kind;
      imm->num_index = im1->num_index;
      return;
    } else {
      imm->const_kind = im2->const_kind;
      imm->num_index = im2->num_index;
      return;
    }
  }

  // if non-complex and complex -> complex
  if ((im1->const_kind == NUM_KIND_COMPLEX) ||
      (im2->const_kind == NUM_KIND_COMPLEX)) {
    if (im2->const_kind == NUM_KIND_COMPLEX) {   // swap im1 to the complex
      Immediate *t = im1;
      im1 = im2;
      im2 = t;
    }
    // WAW: the following needs some fixing (e.g., 128-bit int/uint?)
    if ((im2->const_kind == NUM_KIND_UINT) ||
        (im2->const_kind == NUM_KIND_INT)) {
      if (float_type_precision[im1->num_index] >= int_type_precision[im2->num_index]) {
        imm->num_index = im1->num_index;
      } else { // else, int/uint has greater width?
        imm->num_index =  (int_type_precision[im2->num_index] <= 32) ? FLOAT_SIZE_32 : FLOAT_SIZE_64;
      }
    } else {  // else, im2 must be float?
      imm->num_index = (im1->num_index >= im2->num_index) ? im1->num_index : im2->num_index;
      }
    im1->const_kind = NUM_KIND_COMPLEX;
    return;
  }

  if (im2->const_kind == NUM_KIND_FLOAT) {
    Immediate *t = im2; im2 = im1; im1 = t;
  }
  if (im1->const_kind == NUM_KIND_FLOAT) {
    if (int_type_precision[im2->const_kind] <= float_type_precision[im1->const_kind]) {
      imm->const_kind = im1->const_kind;
      imm->num_index = im1->num_index;
      return;
    }
    if (int_type_precision[im2->const_kind] <= 32) {
      imm->const_kind = NUM_KIND_FLOAT;
      imm->num_index = FLOAT_SIZE_32;
      return;
    }
    imm->const_kind = NUM_KIND_FLOAT;
    imm->num_index = FLOAT_SIZE_64;
    return;
  }
  // mixed signed and unsigned
  if (im1->num_index >= INT_SIZE_64 || im2->num_index >= INT_SIZE_64) {
    imm->const_kind = NUM_KIND_INT;
    imm->num_index = INT_SIZE_64;
    return;
  } else if (im1->num_index >= INT_SIZE_32 || im2->num_index >= INT_SIZE_32) {
    imm->const_kind = NUM_KIND_INT;
    imm->num_index = INT_SIZE_32;
    return;
  } else if (im1->num_index >= INT_SIZE_16 || im2->num_index >= INT_SIZE_16) {
    imm->const_kind = NUM_KIND_INT;
    imm->num_index = INT_SIZE_16;
    return;
  } else if (im1->num_index >= INT_SIZE_8 || im2->num_index >= INT_SIZE_8) {
    imm->const_kind = NUM_KIND_INT;
    imm->num_index = INT_SIZE_8;
    return;
  }
  imm->const_kind = NUM_KIND_UINT;
  imm->num_index = INT_SIZE_1;
  return;
}

void
fold_constant(int op, Immediate *aim1, Immediate *aim2, Immediate *imm) {
  Immediate im1(*aim1), im2, coerce;
  if (aim2)
    im2 = *aim2;
  switch (op) {
    default: INT_FATAL("fold constant op not supported"); break;
    case P_prim_mult:
    case P_prim_div:
    case P_prim_mod:
    case P_prim_add:
    case P_prim_subtract:
    case P_prim_and:
    case P_prim_or:
    case P_prim_xor:
    case P_prim_pow:
      fold_result(&im1, &im2, &coerce);
      imm->const_kind = coerce.const_kind;
      imm->num_index = coerce.num_index;
      break;
    case P_prim_lsh:
    case P_prim_rsh:
      imm->const_kind = im1.const_kind;
      imm->num_index = im1.num_index;
      break;
    case P_prim_less:
    case P_prim_lessorequal:
    case P_prim_greater:
    case P_prim_greaterorequal:
    case P_prim_equal:
    case P_prim_notequal:
      fold_result(&im1, &im2, &coerce);
      imm->const_kind = NUM_KIND_UINT;
      imm->num_index = INT_SIZE_1;
      break;
    case P_prim_land:
    case P_prim_lor:
    case P_prim_lnot:
      coerce.const_kind = imm->const_kind = NUM_KIND_UINT;
      coerce.num_index = imm->num_index = INT_SIZE_1;
      break;
    case P_prim_plus:
    case P_prim_minus:
    case P_prim_not:
      imm->const_kind = im1.const_kind;
      imm->num_index = im1.num_index;
      break;
  }
  if (coerce.const_kind) {
    coerce_immediate(&im1, &coerce);
    im1 = coerce;
    if (aim2) {
      coerce_immediate(&im2, &coerce);
      im2 = coerce;
    }
  }
  switch (op) {
    default: INT_FATAL("fold constant op not supported"); break;
    case P_prim_mult: DO_FOLD(*); break;
    case P_prim_div: DO_FOLD(/); break;
    case P_prim_mod: DO_FOLDI(%); break;
    case P_prim_add: DO_FOLD(+); break;
    case P_prim_subtract: DO_FOLD(-); break;
    case P_prim_lsh: DO_FOLDI(<<); break;
    case P_prim_rsh: DO_FOLDI(>>); break;
    case P_prim_less: DO_FOLDB(<); break;
    case P_prim_lessorequal: DO_FOLDB(<=); break;
    case P_prim_greater: DO_FOLDB(>); break;
    case P_prim_greaterorequal: DO_FOLDB(>=); break;
    case P_prim_equal: DO_FOLDB(==); break;
    case P_prim_notequal: DO_FOLDB(!=); break;
    case P_prim_and: DO_FOLDI(&); break;
    case P_prim_xor: DO_FOLDI(^); break;
    case P_prim_or: DO_FOLDI(|); break;
    case P_prim_land: DO_FOLD(&&); break;
    case P_prim_lor: DO_FOLD(||); break;
    case P_prim_plus: DO_FOLD1(+); break;
    case P_prim_minus: DO_FOLD1(-); break;
    case P_prim_not: DO_FOLD1I(~); break;
    case P_prim_lnot: DO_FOLD1(!); break;
  case P_prim_pow: {
    DO_FOLDPOW();
    break;
  }
  }
}

void
convert_string_to_immediate(const char *str, Immediate *imm) {
  switch (imm->const_kind) {
    case NUM_KIND_NONE:
      break;
    case NUM_KIND_UINT: {
      switch (imm->num_index) {
        case INT_SIZE_1:
          if (!strcmp(str, "false")) {
            imm->v_bool = false;
          } else if (!strcmp(str, "true")) {
            imm->v_bool = true;
          } else if (str[0] == '\0') {
            imm->v_bool = !imm->v_bool;
          } else {
            INT_FATAL("Bad bool value");
          }
          break;
        case INT_SIZE_8: 
          if (str[0] != '\'')
            imm->v_uint8 = str2uint8(str);
          else {
            if (str[1] != '\\')
              imm->v_uint8 = str[1];
            else
              imm->v_uint8 = str[2];
          }
          break;
        case INT_SIZE_16:
          imm->v_uint16 = str2uint16(str); break;
        case INT_SIZE_32:
          imm->v_uint32 = str2uint32(str); break;
        case INT_SIZE_64:
          imm->v_uint64 = str2uint64(str); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_INT: {
      switch (imm->num_index) {
        case INT_SIZE_8: 
          if (str[0] != '\'')
            imm->v_int8 = str2int8(str);
          else {
            if (str[1] != '\\')
              imm->v_int8 = str[1];
            else
              imm->v_int8 = str[2];
          }
          break;
        case INT_SIZE_16:
          imm->v_int16 = str2int16(str); break;
        case INT_SIZE_32:
          imm->v_int32 = str2int32(str); break;
        case INT_SIZE_64:
          imm->v_int64 = str2int64(str); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
    }
    case NUM_KIND_FLOAT: case NUM_KIND_IMAG:
      switch (imm->num_index) {
        case FLOAT_SIZE_32:
          imm->v_float32 = atof( str); break;
        case FLOAT_SIZE_64:
          imm->v_float64 = atof( str); break;
        default: INT_FATAL("Unhandled case in switch statement");
      }
      break;
  }
}
