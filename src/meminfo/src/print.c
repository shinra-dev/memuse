/*  Copyright (c) 2014 Drew Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "meminfo.h"
#include <stdio.h>


#define SCALE 1024

static const char *meminfo_names[] = 
  {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"};


/**
 * @file
 * @brief 
 * Memory printer.
 *
 * @details
 * Prints memory values in their "most natural" unit.  For example,
 * 100000 bytes will print as 97.656 KiB.
 *
 * @param val
 * The memory size (in bytes) to be printed in its natural unit.
 *
 * @note
 * Outputs are in IEC (as opposed to SI) prefix.
 *
 * @return
 * Returns MEMINFO_OK.
 */
int meminfo_print_memval(memsize_t val)
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
