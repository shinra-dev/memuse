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
#include "memuse.h"


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



SEXP set_meminfo(double *mem)
{
  R_INIT;
  
  double memunit = mem[MEMUNIT];
  
  SEXP R_list, R_list_names;
  SEXP totalram, freeram, bufferram, memcached;
  
  #if OS_WINDOWS
  SEXP totalpage, freepage;
  #else
  SEXP totalswap, freeswap;
  #endif
  
  newRvec(totalram, 1, "double");
  newRvec(freeram, 1, "double");
  
  
  #if OS_LINUX
  SEXP swapcached;
  
  newRvec(bufferram, 1, "double");
  newRvec(memcached, 1, "double");
  newRvec(totalswap, 1, "double");
  newRvec(freeswap, 1, "double");
  newRvec(swapcached, 1, "double");
  
  DBL(bufferram, 0) = mem[BUFFERRAM] * memunit;
  DBL(memcached, 0) = mem[MEMCACHED] * memunit;
  DBL(totalswap, 0) = mem[TOTALSWAP] * memunit;
  DBL(freeswap, 0) = mem[FREESWAP] * memunit;
  DBL(swapcached, 0) = mem[SWAPCACHED] * memunit;
  
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "bufferram", "cachedram", "totalswap", "freeswap", "swapcached");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, bufferram, memcached, totalswap, freeswap, swapcached);
  #elif OS_WINDOWS
  newRvec(totalpage, 1, "double");
  newRvec(freepage, 1, "double");
  
  DBL(totalpage, 0) = mem[TOTALPAGE];
  DBL(freepage, 0) = mem[FREEPAGE];
  
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "totalpage", "freepage");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, totalpage, freepage);
  #elif OS_MAC
  newRvec(totalswap, 1, "double");
  newRvec(freeswap, 1, "double");
  
  DBL(totalswap, 0) = mem[TOTALSWAP];
  DBL(freeswap, 0) = mem[FREESWAP];
  
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "totalswap", "freeswap");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, totalswap, freeswap);
  #elif OS_FREEBSD
  newRvec(bufferram, 1, "dbl");
  newRvec(memcached, 1, "dbl");
  newRvec(totalswap, 1, "dbl");
  
  DBL(bufferram, 0)  = mem[BUFFERRAM] * memunit;
  DBL(memcached, 0)  = mem[MEMCACHED] * memunit;
  DBL(totalswap, 0)  = mem[TOTALSWAP] * memunit;
  
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "bufferram", "cachedram", "totalswap");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, bufferram, memcached, totalswap);
  #elif OS_NIX
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram);
  #endif
  
  
  REAL(VECTOR_ELT(R_list, TOTALRAM))[0] = mem[TOTALRAM] * memunit;
  REAL(VECTOR_ELT(R_list, FREERAM))[0] = mem[FREERAM] * memunit;
  
  
  R_END;
  return R_list;
}



// Main interface
SEXP R_meminfo()
{
  SEXP R_list;
  
  double *mem;
  int ret;
  
  ret = get_meminfo(&mem);
  
  if (!ret)
    R_list = set_meminfo(mem);
  else
    R_list = meminfo_error(ret);
  
  if (ret != PLATFORM_ERROR)
    free(mem);
  
  return R_list;
}



