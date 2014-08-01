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


/* 
 *           Swap
 */ 

int meminfo_totalswap(uint64_t *totalswap)
{
  int ret;
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *totalswap = info.totalswap * info.mem_unit;
  #elif OS_MAC
  struct xsw_usage vmusage = {0};
  size_t size = sizeof(vmusage);
  sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0);
  *totalswap = vmusage.xsu_total;
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalswap = status.ullTotalPageFile;
  #elif OS_FREEBSD
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  
  *totalswap=0;
  ret = sysctl_val("vm.swap_total", totalswap);
  chkret(ret);
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}


int meminfo_freeswap(uint64_t *freeswap)
{
  int ret;
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *freeswap = info.freeswap * info.mem_unit;
  #elif OS_MAC
  struct xsw_usage vmusage = {0};
  size_t size = sizeof(vmusage);
  sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0);
  *freeswap = vmusage.xsu_avail;
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *freeswap = status.ullAvailPageFile;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}




int meminfo_cachedswap(uint64_t *cachedswap)
{
  int ret;
  
  #if OS_LINUX
  ret = read_proc_file("/proc/meminfo", cachedswap, "SwapCached:", 11);
  
  chkret(ret);
  *cachedswap *= 1024L;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}



