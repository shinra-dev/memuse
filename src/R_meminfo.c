#include <SEXPtools.h>
#include "memuse.h"


// Helpers
void meminfo_error(SEXP R_list)
{
  R_INIT;
  int i;
  SEXP tmp;
  
  for (i=0; i<LENGTH(R_list); i++)
    REAL(VECTOR_ELT(R_list, i))[0] = -1.0;
  
  R_END;
}



void set_meminfo(SEXP R_list, double *mem)
{
  double memunit = mem[MEMUNIT];
  
  REAL(VECTOR_ELT(R_list, TOTALRAM))[0] = mem[TOTALRAM] * memunit;
  REAL(VECTOR_ELT(R_list, FREERAM))[0] = mem[FREERAM] * memunit;
  REAL(VECTOR_ELT(R_list, BUFFERRAM))[0] = mem[BUFFERRAM] * memunit;
  REAL(VECTOR_ELT(R_list, MEMCACHED))[0] = mem[MEMCACHED] * memunit;
  REAL(VECTOR_ELT(R_list, TOTALSWAP))[0] = mem[TOTALSWAP] * memunit;
  REAL(VECTOR_ELT(R_list, FREESWAP))[0] = mem[FREESWAP] * memunit;
}



// Main interface
SEXP R_meminfo()
{
  R_INIT;
  SEXP R_list, R_list_names;
  SEXP totalram, freeram, bufferram, memcached;
  SEXP totalswap, freeswap;
  
  double *mem;
  int ret;
  
  
  newRvec(totalram, 1, "double");
  newRvec(freeram, 1, "double");
  newRvec(bufferram, 1, "double");
  newRvec(memcached, 1, "double");
  newRvec(totalswap, 1, "double");
  newRvec(freeswap, 1, "double");
  
  R_list_names = make_list_names(6, "totalram", "freeram", "bufferram", "cachedram", "totalswap", "freeswap");
  R_list = make_list(R_list_names, 6, totalram, freeram, bufferram, memcached, totalswap, freeswap);
  
  ret = get_meminfo(&mem);
  
  if (!ret)
    set_meminfo(R_list, mem);
  else
    meminfo_error(R_list);
  
  // hope this works, lol
  if (!PLATFORM_ERROR)
    free(mem);
  
  
  R_END;
  return R_list;
}



