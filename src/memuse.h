#ifndef __R_MEMUSE__
#define __R_MEMUSE__


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



#endif
