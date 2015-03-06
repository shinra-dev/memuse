/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"


/**
 * @file
 * @brief 
 * Total Swap
 *
 * @details
 * This function looks up the total swap in bytes.
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the total swap (in bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_totalswap(memsize_t *totalswap)
{
  int ret;
  *totalswap = 0L;
  
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
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
  
  ret = GlobalMemoryStatusEx(&status);
  winchkret(ret, FAILURE);
  
  *totalswap = (memsize_t) status.ullTotalPageFile;
  #elif OS_FREEBSD
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
 * This function looks up the available swap in bytes.
 *
 * @param totalswap
 * Output, passed by reference.  On successful return, the value
 * is set to the free swap (in bytes) available on the system.
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

