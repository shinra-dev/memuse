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

#include <stdint.h>





#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int read_proc_meminfo(uint64_t *val, char *field, int fieldlen)
{
  int tmplen = 1024 * sizeof(char);
  char *tmp;
  long value = -1L;
  
  val[0] = 0;
  
  FILE* fp = fopen("/proc/meminfo", "r");
  
  if (fp != NULL)
  {
    tmp = (char*) malloc(tmplen);
    
    while (getline(&tmp, &tmplen, fp) >= 0)
    {
      if (strncmp(tmp, field, fieldlen) == 0)
      {
        sscanf(tmp, "%*s%ld", &value);
        break;
      }
    }
    
    fclose(fp);
    free((void*)tmp);
    
    if (value != -1L)
    {
      val[0] = (double) (value * 1024L);
      return 0;
    }
  }
  
  return FAILURE;
}

#elif OS_MAC

#include <mach/vm_statistics.h>
#include <mach/mach_types.h> 
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>

int sysctl_val(char *name, double *val)
{
  int ret;
  uint64_t oldp;
  size_t oldlenp;
  oldlenp = sizeof(oldp);
  
  ret = sysctlbyname(name, &oldp, &oldlenp, NULL, 0);
  
  *val = (double) oldp;
  
  return ret;
}


#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#elif OS_FREEBSD

#include <unistd.h>

#include <sys/types.h>
#include <sys/sysctl.h>


int sysctl_val(char *name, double *val)
{
  int ret;
  uint64_t oldp;
  size_t oldlenp;
  oldlenp = sizeof(oldp);
  
  ret = sysctlbyname(name, &oldp, &oldlenp, NULL, 0);
  
  *val = (double) oldp;
  
  return ret;
}

#elif OS_NIX

#include <unistd.h>

#endif





/* 
 *           Ram
 */ 

int meminfo_totalram(uint64_t *totalram)
{
  int ret;
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *totalram = info.totalram * info.mem_unit;
  #elif OS_MAC
  ret = sysctl_val("hw.memsize", totalram);
  chkret(ret);
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalram = status.ullTotalPhys;
  #elif OS_FREEBSD
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  
  ret = sysctl_val("hw.physmem", &totalram);
  chkret(ret);
  #elif OS_NIX
  uint64_t npages, pagesize;
  
  npages = sysconf(_SC_PHYS_PAGES);
  if (npages == FAILURE)
    return FAILURE;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  totalram = npages * pagesize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}



int meminfo_freeram(uint64_t *freeram)
{
  int ret;
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *freeram = info.freeram * info.mem_unit;
  #elif OS_MAC
  vm_size_t page_size;
  mach_port_t mach_port;
  mach_msg_type_number_t count;
  vm_statistics_data_t vm_stats;
  
  mach_port = mach_host_self();
  count = sizeof(vm_stats) / sizeof(natural_t);
  
  ret = host_page_size(mach_port, &page_size);
  if (ret != KERN_SUCCESS)
    return FAILURE;
  
  ret = host_statistics(mach_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count);
  if (ret != KERN_SUCCESS)
    return FAILURE;
  
  *freeram = (uint64_t) vm_stats.free_count * (uint64_t) page_size;
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalram = status.ullAvailPhys;
  #elif OS_FREEBSD
  uint64_t tmp;
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  else
    pagesize = ret;
  
  ret = sysctl_val("vm.stats.vm.v_free_count", &tmp);
  chkret(ret);
  
  *freeram = tmp * pagesize;
  #elif OS_NIX
  uint64_t pagesize, freepages;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  freepages = sysconf(_SC_AVPHYS_PAGES);
  if (freepages == FAILURE)
    return FAILURE;
  
  totalram = pagesize * freepages;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}



int meminfo_bufferram(uint64_t *bufferram)
{
  int ret;
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *bufferram = info.bufferram * info.mem_unit;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}



int meminfo_cachedram(uint64_t *cachedram)
{
  int ret;
  
  #if OS_LINUX
  ret = read_proc_meminfo(cachedram, "Cached:", 7);
  
  chkret(ret);
  #elif OS_FREEBSD
  //FIXME
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}




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
  
  *totalram = status.ullTotalPageFile;
  #elif OS_FREEBSD
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  
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
  *totalswap = vmusage.xsu_avail;
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalram = status.ullAvailPageFile;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}




int meminfo_cachedswap(uint64_t *cachedswap)
{
  int ret;
  
  #if OS_LINUX
  ret = read_proc_meminfo(cachedswap, "SwapCached:", 11);
  
  chkret(ret);
  #else
  return PLATFORM_ERROR;
  #endif
  
  return 0;
}


