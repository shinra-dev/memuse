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
  SEXP ret;
  
  meminfo_process_size(&tmp);
  
  newRvec(ret, 1, "double");
  
  DBL(ret, 0) = (double) tmp;
  
  R_END;
  return ret;
}


