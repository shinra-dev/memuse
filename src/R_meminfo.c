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


SEXP meminfo_error()
{
  R_INIT;
  SEXP R_list_names, R_list, platform;
  
  newRvec(platform, 1, "double");
  
  R_list_names = make_list_names(1, "platform");
  R_list = make_list(R_list_names, 1, platform);
  
  REAL(VECTOR_ELT(R_list, 0))[0] = -1.0;
  
  R_END;
  return R_list;
}



SEXP set_meminfo(double *mem)
{
  R_INIT;
  
  double memunit = mem[MEMUNIT];
  
  SEXP R_list, R_list_names;
  SEXP totalram, freeram, bufferram, memcached;
  SEXP totalswap, freeswap;
  
  newRvec(totalram, 1, "double");
  newRvec(freeram, 1, "double");
  
  
  #if OS_LINUX
  newRvec(bufferram, 1, "double");
  newRvec(memcached, 1, "double");
  newRvec(totalswap, 1, "double");
  newRvec(freeswap, 1, "double");
  
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "bufferram", "cachedram", "totalswap", "freeswap");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, bufferram, memcached, totalswap, freeswap);
  
  REAL(VECTOR_ELT(R_list, BUFFERRAM))[0] = mem[BUFFERRAM] * memunit;
  REAL(VECTOR_ELT(R_list, MEMCACHED))[0] = mem[MEMCACHED] * memunit;
  REAL(VECTOR_ELT(R_list, TOTALSWAP))[0] = mem[TOTALSWAP] * memunit;
  REAL(VECTOR_ELT(R_list, FREESWAP))[0] = mem[FREESWAP] * memunit;
  #elif OS_WINDOWS
  R_list_names = make_list_names(MEMLEN-1, "totalram", "freeram", "totalpage", "freepage");
  R_list = make_list(R_list_names, MEMLEN-1, totalram, freeram, totalpage, freepage);
  
  REAL(VECTOR_ELT(R_list, TOTALPAGE))[0] = mem[TOTALPAGE];
  REAL(VECTOR_ELT(R_list, FREEPAGE))[0] = mem[FREEPAGE];
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
    R_list = meminfo_error();
  
  if (ret != PLATFORM_ERROR)
    free(mem);
  
  return R_list;
}



