//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

// Copyright 2014, Schmidt


#include "memuse.h"

// Constants
SEXP R_meminfo_retvals(SEXP retval)
{
  R_INIT;
  
  PRINT(retval);
  printf("%d %d %d\n", MEMUSE_OK, FAILURE, PLATFORM_ERROR);
  
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
SEXP R_meminfo()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  uint64_t tmp;
  
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



SEXP R_swapinfo()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  uint64_t tmp;
  
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



SEXP R_memuse_process_size()
{
  R_INIT;
  uint64_t tmp;
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



SEXP R_cachesize(SEXP level)
{
  R_INIT;
  
  int ret;
  int ct = 0;
  uint64_t tmp;
  
  SEXP RET;
  
  
  CACHEFUN(cachesize, RET, INT(level));
  
  
  R_END;
  return RET;
}



SEXP R_cachelinesize(SEXP level)
{
  R_INIT;
  
  int ret;
  int ct = 0;
  uint64_t tmp;
  
  SEXP cachelinesize;
  
  
  TRYFUNC(cachelinesize);
  
  
  R_END;
  return cachelinesize;
}

