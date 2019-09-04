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
#include <stdio.h>


/**
 * @file
 * @brief 
 * Total Ram
 *
 * @details
 * This function looks up the total ram in bytes.
 *
 * @param totalram
 * Output, passed by reference.  On successful return, the value
 * is set to the total ram (in bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_totalram(memsize_t *totalram)
{
  int ret = MEMINFO_OK;
  *totalram = 0L;
  
  
#if OS_LINUX
  struct sysinfo info;
  int test = sysinfo(&info);
  chkret(test, FAILURE);
  
  *totalram = (memsize_t) info.totalram * info.mem_unit;
#elif OS_MAC
  int test = sysctl_val("hw.memsize", totalram);
  chkret(test, FAILURE);
#elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  int test = GlobalMemoryStatusEx(&status);
  winchkret(test, FAILURE);
  
  *totalram = (memsize_t) status.ullTotalPhys;
#elif OS_FREEBSD
  int test = sysctl_val("hw.physmem", totalram);
  chkret(test, FAILURE);
#elif OS_NIX
  memsize_t npages, pagesize;
  
  npages = sysconf(_SC_PHYS_PAGES);
  if (npages == (memsize_t)FAILURE)
    return FAILURE;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == (memsize_t)FAILURE)
    return FAILURE;
  
  *totalram = (memsize_t) npages * pagesize;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Free Ram
 *
 * @details
 * This function looks up the available ram in bytes.
 *
 * @param totalram
 * Output, passed by reference.  On successful return, the value
 * is set to the free ram (in bytes) available on the system.
 *
 * @note
 * TODO explain "free"
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_freeram(memsize_t *freeram)
{
  int ret = MEMINFO_OK;
  *freeram = 0L;
  
  
#if OS_LINUX
  struct sysinfo info;
  int test = sysinfo(&info);
  chkret(test, FAILURE);
  
  *freeram = (memsize_t) info.freeram * info.mem_unit;
#elif OS_MAC
  vm_size_t page_size;
  mach_port_t mach_port;
  mach_msg_type_number_t count;
  vm_statistics_data_t vm_stats;
  
  mach_port = mach_host_self();
  count = sizeof(vm_stats) / sizeof(natural_t);
  
  int test = host_page_size(mach_port, &page_size);
  if (test != KERN_SUCCESS)
    return FAILURE;
  
  test = host_statistics(mach_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count);
  if (test != KERN_SUCCESS)
    return FAILURE;
  
  *freeram = (memsize_t) vm_stats.free_count * (memsize_t) page_size;
#elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  int test = GlobalMemoryStatusEx(&status);
  winchkret(test, FAILURE);
  
  *freeram = (memsize_t) status.ullAvailPhys;
#elif OS_FREEBSD
  int page = sysconf(_SC_PAGESIZE);
  if (page == -1)
    return FAILURE;
  
  int test = sysctl_val("vm.stats.vm.v_free_count", freeram);
  chkret(test, FAILURE);
  
  *freeram *= (memsize_t) page;
#elif OS_NIX
  memsize_t pagesize, freepages;
  
  pagesize = (memsize_t) sysconf(_SC_PAGESIZE);
  if (pagesize == (memsize_t)FAILURE)
    return FAILURE;
  
  freepages = (memsize_t) sysconf(_SC_AVPHYS_PAGES);
  if (freepages == (memsize_t)FAILURE)
    return FAILURE;
  
  *freeram = pagesize * freepages;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Buffer Ram
 *
 * @details
 * This function looks up the amount of ram allocated for buffers in bytes.
 *
 * @param totalram
 * Output, passed by reference.  On successful return, the value
 * is set to the amount of ram used for buffers (in bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_bufferram(memsize_t *bufferram)
{
  int ret = MEMINFO_OK;
  *bufferram = 0L;
  
#if OS_LINUX
  struct sysinfo info;
  
  int test = sysinfo(&info);
  chkret(test, FAILURE);
  
  *bufferram = info.bufferram * info.mem_unit;
#elif OS_FREEBSD
  memsize_t v = 0L;
  
  int test = sysctl_val("vfs.bufspace", &v);
  chkret(test, FAILURE);
  
  *bufferram = v;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Cached Ram
 *
 * @details
 * This function looks up the amount of ram used for cache in bytes.
 *
 * @param totalram
 * Output, passed by reference.  On successful return, the value
 * is set to the amount of ram used for disk cache (in bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_cachedram(memsize_t *cachedram)
{
  int ret = MEMINFO_OK;
  *cachedram = 0L;
  
  
#if OS_LINUX
  int test = read_proc_file("/proc/meminfo", cachedram, "Cached:", 7);
  chkret(test, FAILURE);
  
  *cachedram *= 1024L;
#elif OS_FREEBSD
  int page;
  memsize_t v = 0;
  
  page = sysconf(_SC_PAGESIZE);
  if (page == -1)
    return FAILURE;
  
  int test = sysctl_val("vm.stats.vm.v_cache_count", &v);
  chkret(test, FAILURE);
  
  *cachedram = (memsize_t) v*page;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}
