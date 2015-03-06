/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


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
  
  chkret(ret, FAILURE);
  
  *totalram = info.totalram * info.mem_unit;
  #elif OS_MAC
  ret = sysctl_val("hw.memsize", totalram);
  chkret(ret, FAILURE);
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
  chkret(ret, FAILURE);
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
  
  chkret(ret, FAILURE);
  
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
  
  ret = GlobalMemoryStatusEx(&status);
  winchkret(ret, FAILURE);
  
  *freeram = status.ullAvailPhys;
  #elif OS_FREEBSD
  int pagesize;
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  else
    pagesize = ret;
  
  ret = sysctl_val("vm.stats.vm.v_free_count", freeram);
  chkret(ret, FAILURE);
  
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
  
  chkret(ret, FAILURE);
  
  *bufferram = info.bufferram * info.mem_unit;
  #elif OS_FREEBSD
  int ret;
  memsize_t v=0;
  
  ret = sysctl_val("vfs.bufspace",&v);
  
  chkret(ret, FAILURE);
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
  
  chkret(ret, FAILURE);
  *cachedram *= 1024L;
  #elif OS_FREEBSD
  int ret,page;
  memsize_t v=0;
  
  page = sysconf(_SC_PAGESIZE);
  if (page == FAILURE)
    return FAILURE;
  
  ret = sysctl_val("vm.stats.vm.v_cache_count",&v);
  
  chkret(ret, FAILURE);
  *cachedram = v*page;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return MEMINFO_OK;
}

