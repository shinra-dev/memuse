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


#include <SEXPtools.h>
#include "meminfo/meminfo.h"


#define TRYFUNC(THEFUN) ret=meminfo_##THEFUN(&tmp); \
  newRvec(THEFUN, 1, "double"); \
  ct++; \  
  if (ret == MEMUSE_OK) \
    DBL(THEFUN, 0) = (double) tmp; \
  else \
    DBL(THEFUN, 0) = (double) ret



SEXP meminfo_error(int code)
{
  R_INIT;
  SEXP R_list_names, R_list, platform;
  
  newRvec(platform, 1, "double");
  
  R_list_names = make_list_names(1, "platform");
  R_list = make_list(R_list_names, 1, platform);
  
  if (code == FAILURE)
    REAL(VECTOR_ELT(R_list, 0))[0] = ((double) FAILURE);
  else if (code == PLATFORM_ERROR)
    REAL(VECTOR_ELT(R_list, 0))[0] = ((double) PLATFORM_ERROR);
  
  R_END;
  return R_list;
}



SEXP set_meminfo()
{
  R_INIT;
  
  int ret;
  int ct = 0;
  uint64_t tmp;
  
  SEXP R_list, R_list_names;
  SEXP totalram, freeram, bufferram, cachedram;
  SEXP totalswap, freeswap, cachedswap;
  
  totalram = freeram = bufferram = cachedram = NULL;
  totalswap = freeswap = cachedswap = NULL;
  
  TRYFUNC(totalram);
  TRYFUNC(freeram);
  TRYFUNC(bufferram);
  TRYFUNC(cachedram);
  TRYFUNC(totalswap);
  TRYFUNC(freeswap);
  TRYFUNC(cachedswap);
  
  printf("%d %d\n", ct, (int)tmp);
  
  R_list_names = make_list_names(ct, "totalram", "freeram", "bufferram", "cachedram", "totalswap", "freeswap", "cachedswap");
  R_list = make_list(R_list_names, ct, totalram, freeram, bufferram, cachedram, totalswap, freeswap, cachedswap);
  
  
  R_END;
  return R_list;
}



// Main interface
SEXP R_meminfo()
{
  SEXP R_list;
  
  R_list = set_meminfo();
/*    R_list = meminfo_error(ret);*/
  
  return R_list;
}



