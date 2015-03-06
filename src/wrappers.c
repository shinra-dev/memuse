/*
  Copyright (c) 2014-2015, Schmidt
  FreeBSD support improved by Heckendorf, 2014
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
  1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
  
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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



SEXP R_meminfo_system_uptime()
{
  R_INIT;
  int ret;
  SEXP uptime;
  newRvec(uptime, 1, "dbl");
  
  runtime_t time;
  ret = meminfo_system_uptime(&time);
  
  DBL(uptime) = ret==MEMINFO_OK ? (double)time : (double)ret;
  
  R_END;
  return uptime;
}



SEXP R_meminfo_process_utiltime()
{
  R_INIT;
  int ret;
  SEXP utiltime;
  newRvec(utiltime, 2, "dbl");
  
  runtime_t usr, sys;
  ret = meminfo_process_utiltime(&usr, &sys);
  
  if (ret == MEMINFO_OK)
  {
    DBL(utiltime, 0) = (double) usr;
    DBL(utiltime, 1) = (double) sys;
  }
  else
    DBL(utiltime) = (double)ret;
  
  R_END;
  return utiltime;
}



SEXP R_meminfo_process_runtime()
{
  R_INIT;
  int ret;
  SEXP runtime;
  newRvec(runtime, 1, "dbl");
  
  runtime_t time;
  ret = meminfo_process_runtime(&time);
  
  DBL(runtime) = ret==MEMINFO_OK ? (double)time : (double)ret;
  
  R_END;
  return runtime;
}

