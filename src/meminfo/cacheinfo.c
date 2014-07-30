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

#if OS_WINDOWS
typedef BOOL (WINAPI *LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, 
    PDWORD);
#endif

/* 
 *           Cache
 */ 

int meminfo_totalcache(uint64_t *totalcache, const unsigned int level)
{
  int ret;
  
  #if OS_LINUX
  if (level == 1)
    ret = sysconf(_SC_LEVEL1_DCACHE_SIZE);
  if (level == 2)
    ret = sysconf(_SC_LEVEL2_CACHE_SIZE);
  if (level == 3)
    ret = sysconf(_SC_LEVEL3_CACHE_SIZE);
  
  if (ret == 0)
  {
    *totalcache = 0L;
    return FAILURE;
  }
  
  *totalcache = ret;
  #elif OS_MAC
  uint64_t cache_size = 0;
  size_t size = sizeof(cache_size);
  
  if (level == 1)
    ret = sysctlbyname("hw.l1dcachesize", &cache_size, &size, 0, 0);
  else if (level == 2)
    ret = sysctlbyname("hw.l2cachesize", &cache_size, &size, 0, 0);
  else if (level == 3)
    ret = sysctlbyname("hw.l3cachesize", &cache_size, &size, 0, 0);
  else
    return FAILURE;
  
  chkret(ret);  

  if (cache_size == 0)
    return FAILURE;
  
  *totalcache = cache_size;
  #elif OS_WINDOWS
  int i;
  BOOL winret;
  DWORD size = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *slpi;
  
  winret = GetLogicalProcessorInformation(0, &size);
  if (winret == TRUE)
  {
    *totalcache = 0L;
    return FAILURE;
  }
  
  slpi = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(size);
  GetLogicalProcessorInformation(&slpi[0], &size);
  
  *totalcache = 0L;
  
  for (i=0; i != size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
  {
    if (slpi[i].Relationship == RelationCache && slpi[i].Cache.Level == level)
    {
      *totalcache = slpi[i].Cache.Size;
      return 0;
    }
  }
  
  return FAILURE;
  
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}



/* 
 *           Cache
 */ 

int meminfo_cachelinesize(uint64_t *linesize)
{
  int ret;
  
  #if OS_LINUX
  ret = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  
  if (ret == 0)
  {
    *linesize = 0L;
    return FAILURE;
  }
  
  *linesize = ret;
  #elif OS_MAC
  uint64_t cache_size = 0;
  size_t size = sizeof(cache_size);
  
  ret = sysctlbyname("hw.cachelinesize", &cache_size, &size, 0, 0);
  
  chkret(ret);  

  if (cache_size == 0)
    return FAILURE;
  
  *totalcache = cache_size;
  #elif OS_WINDOWS
  int i;
  BOOL winret;
  DWORD size = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *slpi;
  
  winret = GetLogicalProcessorInformation(0, &size);
  if (winret == TRUE)
  {
    *totalcache = 0L;
    return FAILURE;
  }
  
  slpi = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(size);
  GetLogicalProcessorInformation(&slpi[0], &size);
  
  *totalcache = 0L;
  
  for (i=0; i != size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
  {
    if (slpi[i].Relationship == RelationCache && slpi[i].Cache.Level == 1)
    {
      *totalcache = slpi[i].Cache.LineSize;
      return 0;
    }
  }
  
  return FAILURE;
  
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}

