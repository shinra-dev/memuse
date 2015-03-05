/*
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Copyright 2014, Schmidt


#include <RNACI.h>
#include "meminfo/meminfo.h"


#define TRYFUNC(THEFUN) ret=meminfo_##THEFUN(&tmp); \
  newRvec(THEFUN, 1, "double"); \
  ct++; \
  if (ret == MEMUSE_OK) \
    DBL(THEFUN, 0) = (double) tmp; \
  else \
    DBL(THEFUN, 0) = (double) ret

#define CACHEFUN(THEFUN, STORAGE, LEVEL) ret=meminfo_##THEFUN(&tmp, LEVEL); \
  newRvec(STORAGE, 1, "double"); \
  ct++; \
  if (ret == MEMUSE_OK) \
    DBL(STORAGE, 0) = (double) tmp; \
  else \
    DBL(STORAGE, 0) = (double) ret


// Constants
SEXP R_meminfo_retvals(SEXP retval)
{
  R_INIT;
  
  SEXP RET;
  newRvec(RET, 1, "str");
  
  if (INT(retval) == MEMUSE_OK)
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
  
  DBL(uptime) = ret==MEMUSE_OK ? (double)time : (double)ret;
  
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
  
  if (ret == MEMUSE_OK)
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
  
  DBL(runtime) = ret==MEMUSE_OK ? (double)time : (double)ret;
  
  R_END;
  return runtime;
}

