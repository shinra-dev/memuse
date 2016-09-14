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
#include "platform.h"


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
  meminfo_print_memval(val);\
  putchar('\n')

#define BLANKS printf("\n\n")



int main(int argc, char **argv)
{
  int ret;
  cachesize_t cachesize;
  memsize_t memsize;
  
  
  // RAM
  ret = meminfo_totalram(&memsize);
  CHECKANDPRINT(memsize, "totalram:  ");
  
  ret = meminfo_freeram(&memsize);
  CHECKANDPRINT(memsize, "freeram:   ");
  
  ret = meminfo_bufferram(&memsize);
  CHECKANDPRINT(memsize, "bufferram: ");
  
  ret = meminfo_cachedram(&memsize);
  CHECKANDPRINT(memsize, "cachedram: ");
  
  BLANKS;
  
  
  // Swap
  #if OS_WINDOWS
  ret = meminfo_totalswap(&memsize);
  CHECKANDPRINT(memsize, "totalpage:  ");
  
  ret = meminfo_freeswap(&memsize);
  CHECKANDPRINT(memsize, "freepage:   ");
  
  ret = meminfo_cachedswap(&memsize);
  CHECKANDPRINT(memsize, "cachedpage: ");
  #else
  ret = meminfo_totalswap(&memsize);
  CHECKANDPRINT(memsize, "totalswap:  ");
  
  ret = meminfo_freeswap(&memsize);
  CHECKANDPRINT(memsize, "freeswap:   ");
  
  ret = meminfo_cachedswap(&memsize);
  CHECKANDPRINT(memsize, "cachedswap: ");
  #endif
  
  BLANKS;
  
  
  // Cache
  ret = meminfo_cachesize(&cachesize, 0);
  CHECKANDPRINT(cachesize, "L1I: ");
  
  ret = meminfo_cachesize(&cachesize, 1);
  CHECKANDPRINT(cachesize, "L1D: ");
  
  ret = meminfo_cachesize(&cachesize, 2);
  CHECKANDPRINT(cachesize, "L2:  ");
  
  ret = meminfo_cachesize(&cachesize, 3);
  CHECKANDPRINT(cachesize, "L3:  ");
  
  ret = meminfo_cachesize(&cachesize, 4);
  CHECKANDPRINT(cachesize, "L4:  ");
  
  ret = meminfo_cachelinesize(&cachesize);
  CHECKANDPRINT(cachesize, "\nCache Linesize:  ");
  
  BLANKS;
  
  
  // Process RAM usage
  ret = meminfo_process_size(&memsize);
  CHECKANDPRINT(memsize, "RAM Usage for This Program:  ");
  
  return 0;
}
