 /* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

 // Copyright 2014-2016, Drew Schmidt.  All rights reserved.


#include <RNACI.h>
#include "meminfo/src/meminfo.h"


#define TRYFUNC(THEFUN) ret=meminfo_##THEFUN(&tmp); \
  newRvec(THEFUN, 1, "double"); \
  ct++; \
  if (ret == MEMINFO_OK) \
    DBL(THEFUN, 0) = (double) tmp; \
  else \
    DBL(THEFUN, 0) = (double) ret

#define CACHEFUN(THEFUN, STORAGE, LEVEL) ret=meminfo_##THEFUN(&tmp, LEVEL); \
  newRvec(STORAGE, 1, "double"); \
  ct++; \
  if (ret == MEMINFO_OK) \
    DBL(STORAGE, 0) = (double) tmp; \
  else \
    DBL(STORAGE, 0) = (double) ret


// Constants
SEXP R_meminfo_retvals(SEXP retval)
{
  R_INIT;
  
  SEXP RET;
  newRvec(RET, 1, "str");
  
  if (INT(retval) == MEMINFO_OK)
    SET_STRING_ELT(RET, 0, mkChar("ok"));
  else if (INT(retval) == FAILURE)
    SET_STRING_ELT(RET, 0, mkChar("There were errors accessing hardware info; please report this to the package maintainer."));
  else if (INT(retval) == PLATFORM_ERROR)
    SET_STRING_ELT(RET, 0, mkChar("Your operating system is not supported at this time."));
  
  R_END;
  return RET;
}


// Wrappers
SEXP R_meminfo_raminfo()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  memsize_t tmp;
  
  SEXP R_list, R_list_names;
  SEXP totalram, freeram, bufferram, cachedram;
  
  TRYFUNC(totalram);
  TRYFUNC(freeram);
  TRYFUNC(bufferram);
  TRYFUNC(cachedram);
  
  R_list_names = make_list_names(ct, "totalram", "freeram", "bufferram", "cachedram");
  R_list = make_list(R_list_names, ct, totalram, freeram, bufferram, cachedram);
  
  
  R_END;
  return R_list;
}



SEXP R_meminfo_swapinfo()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  memsize_t tmp;
  
  SEXP R_list, R_list_names;
  SEXP totalswap, freeswap, cachedswap;
  
  TRYFUNC(totalswap);
  TRYFUNC(freeswap);
  TRYFUNC(cachedswap);
  
  R_list_names = make_list_names(ct, "totalswap", "freeswap", "cachedswap");
  R_list = make_list(R_list_names, ct, totalswap, freeswap, cachedswap);
  
  
  R_END;
  return R_list;
}



SEXP R_meminfo_procinfo()
{
  R_INIT;
  memsize_t tmp;
  int ct = 0;
  int ret;
  SEXP R_list, R_list_names;
  SEXP process_size, process_peak;
  
  TRYFUNC(process_size);
  TRYFUNC(process_peak);
  
  R_list_names = make_list_names(ct, "size", "peak");
  R_list = make_list(R_list_names, ct, process_size, process_peak);
  
  
  R_END;
  return R_list;
}



SEXP R_meminfo_cacheinfo_size(SEXP level)
{
  R_INIT;
  
  int ret;
  int ct = 0;
  cachesize_t tmp;
  
  SEXP RET;
  
  CACHEFUN(cachesize, RET, INT(level));
  
  R_END;
  return RET;
}



SEXP R_meminfo_cacheinfo_linesize()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  cachesize_t tmp;
  
  SEXP cachelinesize;
  
  TRYFUNC(cachelinesize);
  
  R_END;
  return cachelinesize;
}



SEXP R_meminfo_filesize(SEXP filename)
{
  R_INIT;
  SEXP filesize;
  newRvec(filesize, 1, "dbl");
  
  memsize_t size;
  meminfo_filesize(&size, STR(filename));
  
  DBL(filesize) = (double) size;
  
  R_END;
  return filesize;
}
