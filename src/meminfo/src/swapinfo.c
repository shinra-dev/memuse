/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"


/*
 *           Swap
 */

int meminfo_totalswap(memsize_t *totalswap)
{
  *totalswap = 0L;
  
  
  #if OS_LINUX
  int ret;
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret, FAILURE);
  
  *totalswap = info.totalswap * info.mem_unit;
  #elif OS_MAC
  struct xsw_usage vmusage = {0};
  size_t size = sizeof(vmusage);
  sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0);
  *totalswap = vmusage.xsu_total;
  #elif OS_WINDOWS
  int ret;
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalswap = status.ullTotalPageFile;
  #elif OS_FREEBSD
  int ret;
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  
  *totalswap = 0;
  ret = sysctl_val("vm.swap_total", totalswap);
  chkret(ret, FAILURE);
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}



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
  memsize_t used=0;
  
  *freeswap=0;
  mibsize=sizeof(mib)/sizeof(mib[0]);
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
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *freeswap = status.ullAvailPageFile;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}




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

