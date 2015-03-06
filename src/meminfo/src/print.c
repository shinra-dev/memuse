/* Copyright (c) 2014, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include <stdint.h>
#include <stdio.h>
#include "meminfo.h"


#define SCALE 1024

static const char *meminfo_names[] = 
  {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"};



int meminfo_putval(uint64_t val)
{
  double dval = (double) val;
  double tmp;
  int ind = 0;
  
  tmp = val / SCALE;
  
  while (tmp >= 1.)
  {
    dval = tmp;
    tmp /= (double) SCALE;
    ind++;
  }
  
  if (ind == 0)
    printf("%d %s", (int) val, meminfo_names[ind]);
  else
    printf("%.3f %s", dval, meminfo_names[ind]);
  
  return MEMINFO_OK;
}


