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




