#ifndef P64_ASM_ARG_SLICE_H
#define P64_ASM_ARG_SLICE_H

#include "argtable3.h"
#include <cstdlib>
#include <cstring>
#include <cctype>

typedef struct {
  unsigned long long start;
  unsigned long long size;
} SlicePair;

struct arg_slice {
  struct arg_hdr hdr;
  int count;
  int capacity;
  SlicePair *slices;
};


struct arg_slice* arg_slicen(const char* shortopts,
                             const char* longopts,
                             const char* datatype,
                             int mincount,
                             int maxcount,
                             const char* glossary);

void arg_slice_free(void* parent);

#endif  // P64_ASM_ARG_SLICE_H
