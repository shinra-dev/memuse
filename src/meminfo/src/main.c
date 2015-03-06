/* Copyright (c) 2014, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


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
  
  ret = meminfo_cachelinesize(&cachesize);
  CHECKANDPRINT(cachesize, "\nCache Linesize:  ");
  
  BLANKS;
  
  
  // Process RAM usage
  ret = meminfo_process_size(&memsize);
  CHECKANDPRINT(memsize, "RAM Usage for This Program:  ");
  
  return 0;
}

