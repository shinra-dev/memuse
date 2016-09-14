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
#include "platform.h"


/**
 * @file
 * @brief 
 * Total Swap
 *
 * @details
 * This function looks up the total swap (or pagefile on Windows) in bytes.
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the total swap (in bytes) available on the system.
 *
 * @note
 * For Windows, s/swap/page/g.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_totalswap(memsize_t *totalswap)
{
  *totalswap = 0L;
  
  
#if OS_LINUX
  struct sysinfo info;
  
  int ret = sysinfo(&info);
  chkret(ret, FAILURE);
  
  *totalswap = (memsize_t) info.totalswap * info.mem_unit;
#elif OS_MAC
  struct xsw_usage vmusage = {0};
  size_t size = sizeof(vmusage);
  sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0);
  *totalswap = (memsize_t) vmusage.xsu_total;
#elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  int ret = GlobalMemoryStatusEx(&status);
  winchkret(ret, FAILURE);
  
  *totalswap = (memsize_t) status.ullTotalPageFile;
#elif OS_FREEBSD
  int ret;
  
  ret = sysconf(_SC_PAGESIZE);
  chkret(ret, FAILURE);
  
  ret = sysctl_val("vm.swap_total", totalswap);
  chkret(ret, FAILURE);
#else
  return PLATFORM_ERROR;
#endif
  
  return MEMINFO_OK;
}



/**
 * @file
 * @brief 
 * Free Swap
 *
 * @details
 * This function looks up the available swap (or pagefile on Windows) in bytes.
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the free swap (in bytes) available on the system.
 *
 * @note
 * For Windows, s/swap/page/g.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_freeswap(memsize_t *freeswap)
{
  *freeswap = 0L;
  
  
#if OS_LINUX
  int ret;
  
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret, FAILURE);
  
  *freeswap = info.freeswap * info.mem_unit;
#elif OS_MAC
  struct xsw_usage vmusage = {0};
  size_t size = sizeof(vmusage);
  sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0);
  *freeswap = vmusage.xsu_avail;
#elif OS_FREEBSD
  /* Inspired by FreeBSD 9.1 source for /sbin/swapon */
  struct xswdev xsw;
  size_t mibsize,size;
  int mib[16];
  int i,n;
  int page=getpagesize();
  memsize_t used = 0L;
  
  mibsize = sizeof(mib)/sizeof(mib[0]);
  if(sysctl_mib("vm.swap_info",mib,&mibsize)==-1)
    return FAILURE;
  
  for(i=0;;i++){
    mib[mibsize]=i;
    size=sizeof(xsw);
    
    if(sysctlmib_val(mib,mibsize,&xsw,&size)==-1)
      break;
    
    used+=xsw.xsw_used*page;
  }
  if(meminfo_totalswap(freeswap))
    return FAILURE;
  
  *freeswap-=used;
#elif OS_WINDOWS
  int ret;
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  ret = GlobalMemoryStatusEx(&status);
  winchkret(ret, FAILURE);
  
  *freeswap = (memsize_t) status.ullAvailPageFile;
#else
  return PLATFORM_ERROR;
#endif
  
  return MEMINFO_OK;
}



/**
 * @file
 * @brief 
 * Cached Swap
 *
 * @details
 * TODO I forgot what this does ;_;
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the amount of cached swap (in bytes) on the system.
 *
 * @note
 * Only available on Linux.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_cachedswap(memsize_t *cachedswap)
{
  *cachedswap = 0L;
  
  
  #if OS_LINUX
  int ret;
  
  ret = read_proc_file("/proc/meminfo", cachedswap, "SwapCached:", 11);
  
  chkret(ret, FAILURE);
  *cachedswap *= 1024L;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}
