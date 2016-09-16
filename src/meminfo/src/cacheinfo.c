/*  Copyright (c) 2014-2016 Drew Schmidt
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


/* 
 *           Cache sizes
 */ 

/**
 * @file
 * @brief 
 * Cache Size
 *
 * @details
 * This function looks up the size of the requested cache level
 * in bytes.  Levels may range from 0 to 3; level=0 is the level 1
 * instruction cache, while level=1 is the level 1 data cache.
 *
 * @param totalcache
 * Output, passed by reference.  On successful return, the value
 * is set to the cache size (in bytes) of the requested level.
 * @param level
 * Input.  The desired cache level.
 *
 * @note
 * Requesting a bad cache will result in the return of CACHE_ERROR.
 * As usual, other internal failures will result in the return of
 * FAILURE.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_cachesize(cachesize_t *totalcache, const int level)
{
  *totalcache = 0L;
  if (level > 3 || level < 0)
    return CACHE_ERROR;
  
#if OS_LINUX
  cachesize_t cache_size = 0;
  int name;
  
  if (level == 0)
    name = _SC_LEVEL1_ICACHE_SIZE;
  else if (level == 1)
    name = _SC_LEVEL1_DCACHE_SIZE;
  else if (level == 2)
    name = _SC_LEVEL2_CACHE_SIZE;
  else // if (level == 3)
    name = _SC_LEVEL3_CACHE_SIZE;
  // else if (level == 4)
  //   name = _SC_LEVEL4_CACHE_SIZE;
  
  cache_size = (cachesize_t) sysconf(name);
  
  if (cache_size == 0)
    return FAILURE;
  
  *totalcache = cache_size;
#elif OS_MAC
  cachesize_t cache_size;
  size_t size = sizeof(cache_size);
  char *name;
  
  if (level == 0)
    name = "hw.l1icachesize";
  else if (level == 1)
    name = "hw.l1dcachesize";
  else if (level == 2)
    name = "hw.l2cachesize";
  else // if (level == 3)
    name = "hw.l3cachesize";
  
  int ret = sysctlbyname(name, &cache_size, &size, NULL, 0);
  chkret(ret, CACHE_ERROR);
  
  if (cache_size == 0)
    return FAILURE;
  
  *totalcache = cache_size;
#elif OS_WINDOWS
  int i, winlevel;
  BOOL winret;
  DWORD size = 0;
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *slpi;
  // PROCESSOR_CACHE_TYPE cachetype;
  
  if (level == 0)
  {
    winlevel = 1;
    // cachetype = CacheInstruction;
  }
  else if (level == 1)
  {
    winlevel = 1;
    // cachetype= CacheData;
  }
  else
  {
    winlevel = level;
    // cachetype = CacheUnified;
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
      *totalcache = (cachesize_t) slpi[i].Cache.Size;
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

/**
 * @file
 * @brief 
 * Cache Line Size
 *
 * @details
 * This function looks up the cache line size in bytes.
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the cache line size (in bytes) for the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_cachelinesize(cachesize_t *linesize)
{
  *linesize = 0L;
  
#if OS_LINUX
  cachesize_t cache_size = (cachesize_t) sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  
  if (cache_size == 0) return FAILURE;
  
  *linesize = cache_size;
#elif OS_MAC
  cachesize_t cache_size;
  size_t size = sizeof(cache_size);
  
  int ret = sysctlbyname("hw.cachelinesize", &cache_size, &size, 0, 0);
  chkret(ret, FAILURE);
  
  if (cache_size == 0)
    return FAILURE;
  
  *linesize = cache_size;
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
      *linesize = (cachesize_t) slpi[i].Cache.LineSize;
      return MEMINFO_OK;
    }
  }
  
  return FAILURE;
  
#else
  return PLATFORM_ERROR;
#endif
  
  return MEMINFO_OK;
}
