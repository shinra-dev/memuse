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
#include <stdint.h>


#define TRYFUNC(THEFUN) ret=meminfo_process_##THEFUN(&tmp); \
  newRvec(THEFUN, 1, "double"); \
  ct++; \
  if (ret == 0) \
    DBL(THEFUN, 0) = (double) tmp; \
  else \
    DBL(THEFUN, 0) = (double) ret

// Just for testing
SEXP R_memuse_getpid()
{
  R_INIT;
  uint64_t tmp;
  
  meminfo_getpid(&tmp);
  
  Rprintf("pid=%lld\n", tmp);
  
  R_END;
  return R_NilValue;
}



SEXP R_memuse_process_size()
{
  R_INIT;
  uint64_t tmp;
  int ct = 0;
  int ret;
  SEXP R_list, R_list_names;
  SEXP size, peak;
  
  TRYFUNC(size);
  TRYFUNC(peak);
  
  R_list_names = make_list_names(ct, "size", "peak");
  R_list = make_list(R_list_names, ct, size, peak);
  
  
  R_END;
  return R_list;
}


