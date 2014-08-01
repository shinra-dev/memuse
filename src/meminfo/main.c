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


#if OS_LINUX
  #define HDDRAM swap
#else
  #define HDDRAM page
#endif


int main(int argc, char **argv)
{
  int ret;
  uint16_t tmp16;
  uint32_t tmp32;
  uint64_t tmp64;
  
  
  // RAM
  ret = meminfo_totalram(&tmp64);
  CHECKANDPRINT(tmp64, "totalram:  ");
  
  ret = meminfo_freeram(&tmp64);
  CHECKANDPRINT(tmp64, "freeram:   ");
  
  ret = meminfo_bufferram(&tmp64);
  CHECKANDPRINT(tmp64, "bufferram: ");
  
  ret = meminfo_cachedram(&tmp64);
  CHECKANDPRINT(tmp64, "cachedram: ");
  
  BLANKS;
  
  
  // Swap
  #if OS_WINDOWS
  ret = meminfo_totalswap(&tmp64);
  CHECKANDPRINT(tmp64, "totalpage:  ");
  
  ret = meminfo_freeswap(&tmp64);
  CHECKANDPRINT(tmp64, "freepage:   ");
  
  ret = meminfo_cachedswap(&tmp64);
  CHECKANDPRINT(tmp64, "cachedpage: ");
  #else
  ret = meminfo_totalswap(&tmp64);
  CHECKANDPRINT(tmp64, "totalswap:  ");
  
  ret = meminfo_freeswap(&tmp64);
  CHECKANDPRINT(tmp64, "freeswap:   ");
  
  ret = meminfo_cachedswap(&tmp64);
  CHECKANDPRINT(tmp64, "cachedswap: ");
  #endif
  
  BLANKS;
  
  
  // Cache
  ret = meminfo_cachesize(&tmp32, 0);
  CHECKANDPRINT(tmp32, "L1I: ");
  
  ret = meminfo_cachesize(&tmp32, 1);
  CHECKANDPRINT(tmp32, "L1D: ");
  
  ret = meminfo_cachesize(&tmp32, 2);
  CHECKANDPRINT(tmp32, "L2:  ");
  
  ret = meminfo_cachesize(&tmp32, 3);
  CHECKANDPRINT(tmp32, "L3:  ");
  
  ret = meminfo_cachelinesize(&tmp16);
  CHECKANDPRINT(tmp16, "\nCache Linesize:  ");
  
  BLANKS;
  
  
  // Process RAM usage
  ret = meminfo_process_size(&tmp64);
  CHECKANDPRINT(tmp64, "RAM Usage for This Program:  ");
  
  return 0;
}

