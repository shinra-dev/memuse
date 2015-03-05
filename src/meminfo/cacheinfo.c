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


#include "meminfo.h"
#include "platform.h"



/* 
 *           Cache sizes
 */ 

// level=0 is level-1 instruction cache, level=1 is level-1 data cache

int meminfo_cachesize(cachesize_t *totalcache, const unsigned int level)
{
  *totalcache = 0;
  
  
  #if OS_LINUX
  int ret = MEMINFO_OK;
  
  if (level == 0)
    ret = sysconf(_SC_LEVEL1_ICACHE_SIZE);
  else if (level == 1)
    ret = sysconf(_SC_LEVEL1_DCACHE_SIZE);
  else if (level == 2)
    ret = sysconf(_SC_LEVEL2_CACHE_SIZE);
  else if (level == 3)
    ret = sysconf(_SC_LEVEL3_CACHE_SIZE);
  
  if (ret == 0)
  {
    *totalcache = 0;
    return FAILURE;
  }
  
  *totalcache = ret;
  #elif OS_MAC
  int ret = MEMINFO_OK;
  
  uint64_t cache_size = 0;
  size_t size = sizeof(cache_size);
  
  if (level == 0)
    ret = sysctlbyname("hw.l1icachesize", &cache_size, &size, NULL, 0);
  else if (level == 1)
    ret = sysctlbyname("hw.l1dcachesize", &cache_size, &size, NULL, 0);
  else if (level == 2)
    ret = sysctlbyname("hw.l2cachesize", &cache_size, &size, NULL, 0);
  else if (level == 3)
    ret = sysctlbyname("hw.l3cachesize", &cache_size, &size, NULL, 0);
  else
    return FAILURE;
  
  chkret(ret);
  
  if (cache_size == 0)
    return FAILURE;
  
  *totalcache = (cachesize_t) cache_size;
  #elif OS_WINDOWS
  int i, winlevel;
  BOOL winret;
  DWORD size = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *slpi;
  PROCESSOR_CACHE_TYPE cachetype;
  
  if (level == 0)
  {
    winlevel = 1;
    cachetype = CacheInstruction;
  }
  else if (level == 1)
  {
    winlevel = 1;
    cachetype= CacheData;
  }
  else
  {
    winlevel = level;
    cachetype = CacheUnified;
  }
  
  *totalcache = 0L;
  
  winret = GetLogicalProcessorInformation(0, &size);
  if (winret == TRUE)
    return FAILURE;
  
  slpi = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(size);
  GetLogicalProcessorInformation(&slpi[0], &size);
  
  for (i=0; i != size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
  {
    if (slpi[i].Relationship == RelationCache && slpi[i].Cache.Level == winlevel)
    {
      *totalcache = slpi[i].Cache.Size;
      return MEMINFO_OK;
    }
  }
  
  return FAILURE;
  
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}



/* 
 *           Cache linesize
 */ 

int meminfo_cachelinesize(cachesize_t *linesize)
{
  *linesize = 0;
  
  
  #if OS_LINUX
  int ret;
  
  ret = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  
  if (ret == 0)
  {
    *linesize = 0;
    return FAILURE;
  }
  
  *linesize = (uint16_t) ret;
  #elif OS_MAC
  int ret;
  uint64_t cache_size = 0;
  size_t size = sizeof(cache_size);
  
  ret = sysctlbyname("hw.cachelinesize", &cache_size, &size, 0, 0);
  
  chkret(ret);  

  if (cache_size == 0)
    return FAILURE;
  
  *linesize = (cachesize_t) cache_size;
  #elif OS_WINDOWS
  int i;
  BOOL winret;
  DWORD size = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *slpi;
  
  *linesize = 0;
  
  winret = GetLogicalProcessorInformation(0, &size);
  if (winret == TRUE)
    return FAILURE;
  
  slpi = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(size);
  GetLogicalProcessorInformation(&slpi[0], &size);
  
  for (i=0; i != size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
  {
    if (slpi[i].Relationship == RelationCache && slpi[i].Cache.Level == 1)
    {
      *linesize = slpi[i].Cache.LineSize;
      return MEMINFO_OK;
    }
  }
  
  return FAILURE;
  
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}

