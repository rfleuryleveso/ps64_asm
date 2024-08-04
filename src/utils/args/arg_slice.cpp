//
// Created by Administrator on 04/08/2024.
//

#include "include/utils/args/arg_slice.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "argtable3.h"
#include "argtable3_private.h"

static unsigned long long parse_size(const char* str) {
  char* endptr;
  unsigned long long value = strtoull(str, &endptr, 0);

  if (*endptr == 'k' || *endptr == 'K') {
    value *= 1024ULL;
  } else if (*endptr == 'm' || *endptr == 'M') {
    value *= 1024ULL * 1024ULL;
  } else if (*endptr == 'g' || *endptr == 'G') {
    value *= 1024ULL * 1024ULL * 1024ULL;
  }

  return value;
}

static int arg_slice_scanfn(struct arg_slice* parent, const char* argval) {
  char* str = strdup(argval);
  char* size_str = strchr(str, ',');

  if (size_str) {
    *size_str = '\0';
    size_str++;

    if (parent->count < parent->capacity) {
      parent->slices[parent->count].start = parse_size(str);
      parent->slices[parent->count].size = parse_size(size_str);
      parent->count++;
    }
  }

  free(str);
  return 0;
}

static int arg_slice_checkfn(struct arg_slice* parent) {
  int errorcode = (parent->count < parent->hdr.mincount) ? ARG_ERR_MINCOUNT : 0;

  ARG_TRACE(("%s:checkfn(%p) returns %d\n", __FILE__, parent, errorcode));
  return errorcode;
}

static void arg_slice_errorfn(struct arg_slice* parent, arg_dstr_t ds, int errorcode, const char* argval, const char* progname) {
  const char* shortopts = parent->hdr.shortopts;
  const char* longopts = parent->hdr.longopts;
  const char* datatype = parent->hdr.datatype;

  /* make argval NULL safe */
  argval = argval ? argval : "";

  arg_dstr_catf(ds, "%s: ", progname);
  switch (errorcode) {
    case ARG_ERR_MINCOUNT:
      arg_dstr_cat(ds, "missing option ");
      arg_print_option_ds(ds, shortopts, longopts, datatype, "\n");
      break;

    case ARG_ERR_MAXCOUNT:
      arg_dstr_cat(ds, "excess option ");
      arg_print_option_ds(ds, shortopts, longopts, argval, "\n");
      break;

    default:
      arg_dstr_catf(ds, "unknown error at \"%s\"\n", argval);
  }
}

static void arg_slice_resetfn(struct arg_slice* parent) {
  parent->count = 0;
}

struct arg_slice* arg_slicen(const char* shortopts,
                             const char* longopts,
                             const char* datatype,
                             int mincount,
                             int maxcount,
                             const char* glossary) {
  struct arg_slice* result;

  /* foolproof things by ensuring maxcount is not less than mincount */
  maxcount = (maxcount < mincount) ? mincount : maxcount;

  result = (struct arg_slice*)malloc(sizeof(struct arg_slice));
  if (result) {
    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<start>,<size>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_slice_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_slice_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_slice_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_slice_errorfn;

    result->slices = (SlicePair*)malloc(maxcount * sizeof(SlicePair));
    result->count = 0;
    result->capacity = maxcount;
  }

  return result;
}

void arg_slice_free(void* parent) {
  struct arg_slice* p = (struct arg_slice*)parent;
  if (p) {
    free(p->slices);
    free(p);
  }
}