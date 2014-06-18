#ifndef __R_MEMUSE__
#define __R_MEMUSE__


#include <SEXPtools.h>
#include "meminfo/meminfo.h"


#define TRYFUNC(THEFUN) ret=meminfo_##THEFUN(&tmp); \
  newRvec(THEFUN, 1, "double"); \
  ct++; \
  if (ret == MEMUSE_OK) \
    DBL(THEFUN, 0) = (double) tmp; \
  else \
    DBL(THEFUN, 0) = (double) ret



#endif
