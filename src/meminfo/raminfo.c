/*
  Copyright (c) 2014-2015, Schmidt
  FreeBSD support improved by Heckendorf, 2014
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
 *           Ram
 */

int meminfo_totalram(memsize_t *totalram)
{
  int ret;
  
  *totalram = 0L;
  
  
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
  
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *totalram = status.ullTotalPhys;
  #elif OS_FREEBSD
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  
  *totalram = 0;
  ret = sysctl_val("hw.physmem", totalram);
  chkret(ret);
  #elif OS_NIX
  memsize_t npages, pagesize;
  
  npages = sysconf(_SC_PHYS_PAGES);
  if (npages == FAILURE)
    return FAILURE;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  *totalram = npages * pagesize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}



int meminfo_freeram(memsize_t *freeram)
{
  int ret;
  
  *freeram = 0L;
  
  
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
  
  *freeram = (memsize_t) vm_stats.free_count * (memsize_t) page_size;
  #elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  *freeram = status.ullAvailPhys;
  #elif OS_FREEBSD
  int pagesize;
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  else
    pagesize = ret;
  
  ret = sysctl_val("vm.stats.vm.v_free_count", freeram);
  chkret(ret);
  
  *freeram *= (memsize_t) pagesize;
  #elif OS_NIX
  memsize_t pagesize, freepages;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  freepages = sysconf(_SC_AVPHYS_PAGES);
  if (freepages == FAILURE)
    return FAILURE;
  
  *freeram = pagesize * freepages;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}


#include <stdio.h>
int meminfo_bufferram(memsize_t *bufferram)
{
  *bufferram = 0L;
  
  #if OS_LINUX
  int ret;
  
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
  *bufferram = info.bufferram * info.mem_unit;
  #elif OS_FREEBSD
  int ret;
  memsize_t v=0;
  
  ret = sysctl_val("vfs.bufspace",&v);
  
  chkret(ret);
  *bufferram = v;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}



int meminfo_cachedram(memsize_t *cachedram)
{
  *cachedram = 0L;
  
  
  #if OS_LINUX
  int ret;
  
  ret = read_proc_file("/proc/meminfo", cachedram, "Cached:", 7);
  
  chkret(ret);
  *cachedram *= 1024L;
  #elif OS_FREEBSD
  int ret,page;
  memsize_t v=0;
  
  page = sysconf(_SC_PAGESIZE);
  if (page == FAILURE)
    return FAILURE;
  
  ret = sysctl_val("vm.stats.vm.v_cache_count",&v);
  
  chkret(ret);
  *cachedram = v*page;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}

