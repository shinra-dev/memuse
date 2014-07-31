/*
  Copyright (c) 2014, Schmidt
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

#include <stdint.h>
#include <stdio.h>

#include "platform.h"
#include "meminfo.h"

#define CHECKRET(ret) if(ret==FAILURE)\
  return FAILURE;\
  else if (ret==PLATFORM_ERROR)\
  return PLATFORM_ERROR;

#define CHECKANDPRINT(val,str) \
  printf(str);\
  if (ret==FAILURE) \
  printf("Operation not available on this platform"); \
  else if(ret==PLATFORM_ERROR) \
  printf("Operating system is not supported"); \
  else \
  meminfo_putval(val);\
  putchar('\n')

#define BLANKS printf("\n\n")



int main(int argc, char **argv)
{
  int ret;
  uint64_t tmp;
  
  
  // RAM
  ret = meminfo_totalram(&tmp);
  CHECKANDPRINT(tmp, "totalram:  ");
  
  ret = meminfo_freeram(&tmp);
  CHECKANDPRINT(tmp, "freeram:   ");
  
  ret = meminfo_bufferram(&tmp);
  CHECKANDPRINT(tmp, "bufferram: ");
  
  ret = meminfo_cachedram(&tmp);
  CHECKANDPRINT(tmp, "cachedram: ");
  
  BLANKS;
  
  
  // Swap
  ret = meminfo_totalswap(&tmp);
  CHECKANDPRINT(tmp, "totalswap:  ");
  
  ret = meminfo_freeswap(&tmp);
  CHECKANDPRINT(tmp, "freeswap:   ");
  
  ret = meminfo_cachedswap(&tmp);
  CHECKANDPRINT(tmp, "cachedswap: ");
  
  BLANKS;
  
  
  // Cache
  ret = meminfo_cachesize(&tmp, 1);
  CHECKANDPRINT(tmp, "L1:  ");
  
  ret = meminfo_cachesize(&tmp, 2);
  CHECKANDPRINT(tmp, "L2:  ");
  
  ret = meminfo_cachesize(&tmp, 3);
  CHECKANDPRINT(tmp, "L3:  ");
  
  ret = meminfo_cachelinesize(&tmp);
  CHECKANDPRINT(tmp, "\nCache Linesize:  ");
  
  BLANKS;
  
  
  // Process RAM usage
  ret = meminfo_process_size(&tmp);
  CHECKANDPRINT(tmp, "RAM Usage for This Program:  ");
  
  return 0;
}

