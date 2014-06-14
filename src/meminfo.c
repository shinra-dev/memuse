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


#include "memuse.h"
#define chkret(ret) if(ret)return(ret)



#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int read_proc_meminfo(double *memcached, char *field, int fieldlen)
{
  int tmplen = 1024 * sizeof(char);
  char *tmp;
  long value = -1L;
  
  memcached[0] = 0;
  
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
      memcached[0] = (double) (value * 1024L);
      return 0;
    }
  }
  
  return FAILURE;
}

int get_meminfo(double **mem)
{
  int ret;
  double cached;
  
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  
  // cached
  ret = read_proc_meminfo(&cached, "Cached", 6);
  
  chkret(ret);
  (*mem)[MEMCACHED] = cached;
  
  
  // swap cached
  ret = read_proc_meminfo(&cached, "SwapCached", 10);
  
  chkret(ret);
  (*mem)[SWAPCACHED] = cached;
  
  
  // everything else
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  (*mem)[MEMUNIT] = (double) info.mem_unit;
  
  (*mem)[TOTALRAM] = ((double) info.totalram) * (*mem)[MEMUNIT];
  (*mem)[FREERAM] = ((double) info.freeram) * (*mem)[MEMUNIT];
  (*mem)[BUFFERRAM] = ((double) info.bufferram) * (*mem)[MEMUNIT];
  (*mem)[TOTALSWAP] = ((double) info.totalswap) * (*mem)[MEMUNIT];
  (*mem)[FREESWAP] = ((double) info.freeswap) * (*mem)[MEMUNIT];
  
  return ret;
}



// --------------------------------------------------------
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



int get_meminfo(double **mem)
{
  int ret;
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  vm_size_t page_size;
  mach_port_t mach_port;
  mach_msg_type_number_t count;
  vm_statistics_data_t vm_stats;
  
  size_t size;  
  
  // Ram
  mach_port = mach_host_self();
  count = sizeof(vm_stats) / sizeof(natural_t);
  
  ret = host_page_size(mach_port, &page_size);
  if (ret != KERN_SUCCESS)
    return FAILURE;
  
  ret = host_statistics(mach_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count);
  if (ret != KERN_SUCCESS)
    return FAILURE;
  
  double totram;
  ret = sysctl_val("hw.memsize", &totram);
  chkret(ret);

  (*mem)[TOTALRAM] = ((double) totram); 
  
  (*mem)[FREERAM] = ((double) (int64_t)vm_stats.free_count * (int64_t)page_size);
  
  // Swap
  double totalswap;
  ret = sysctl_val("vm.swapusage", &totalswap);
  chkret(ret);
  (*mem)[TOTALSWAP] = totalswap;

  struct statfs stats;
  ret = statfs("/", &stats);
  chkret(ret);
 (*mem)[FREESWAP] = (double) ((uint64_t)stats.f_bsize * stats.f_bfree);


struct xsw_usage vmusage = {0};
size_t vmusage_size = sizeof(vmusage);
 sysctlbyname("vm.swapusage", &vmusage, &vmusage_size, NULL, 0);
 (*mem)[TOTALSWAP] = (double) vmusage.xsu_total;
 (*mem)[FREESWAP] = (double) vmusage.xsu_avail;

  (*mem)[MEMUNIT] = 1.0;
  
  return 0;
}



// --------------------------------------------------------
#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int get_meminfo(double **mem)
{
  int ret;
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  // "If the function succeeds, the return value is nonzero."
  // Go fuck yourself, Windows.
  ret = GlobalMemoryStatusEx(&status);
  
  if (ret == 0)
    return FAILURE;
  
  (*mem)[MEMUNIT] = 1.0;
  
  (*mem)[TOTALRAM] = ((double) status.ullTotalPhys);
  (*mem)[FREERAM] = ((double) status.ullAvailPhys);
  (*mem)[TOTALPAGE] = ((double) status.ullTotalPageFile);
  (*mem)[FREEPAGE] = ((double) status.ullAvailPageFile);
  
  
  return 0;
}


// --------------------------------------------------------
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


int get_meminfo(double **mem)
{
  int ret;
  double val, pagesize;
  
  *mem = malloc(MEMLEN * sizeof(*mem));
  (*mem)[MEMUNIT] = 1.0;
  
  /* This sets val to something insane for some reason ???
  ret = sysctl_val("hw.pagesize", &val);
  chkret(ret);
  pagesize = val;
  */
  ret = sysconf(_SC_PAGESIZE);
  if (ret == FAILURE)
    return FAILURE;
  else
    pagesize = (double) ret;
  
  
  ret = sysctl_val("hw.physmem", &val);
  chkret(ret);
  (*mem)[TOTALRAM] = val;
  
  ret = sysctl_val("vm.stats.vm.v_free_count", &val);
  chkret(ret);
  (*mem)[FREERAM] = val * pagesize;
  
  ret = sysctl_val("vm.stats.vm.v_active_count", &val);
  chkret(ret);
  (*mem)[BUFFERRAM] = val * pagesize;
  
  ret = sysctl_val("vm.stats.vm.v_cache_count", &val);
  chkret(ret);
  (*mem)[MEMCACHED] = val * pagesize;
  
  
  ret = sysctl_val("vm.swap_total", &val);
  chkret(ret);
  (*mem)[TOTALSWAP] = val;
  
  return 0;
}


// --------------------------------------------------------
#elif OS_NIX // Misc nix's

#include <unistd.h>

int get_meminfo(double **mem)
{
  uint64_t npages, pagesize, freepages;
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  
  npages = sysconf(_SC_PHYS_PAGES);
  if (npages == FAILURE)
    return FAILURE;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  freepages = sysconf(_SC_AVPHYS_PAGES);
  if (freepages == FAILURE)
    return FAILURE;
  
  (*mem)[MEMUNIT] = 1.0;
  
  (*mem)[TOTALRAM] = (double) (npages * pagesize);
  (*mem)[FREERAM] = (double) (pagesize * freepages);
  
  
  return 0;
}



// --------------------------------------------------------
#else


int get_meminfo(double **mem)
{
  return PLATFORM_ERROR;
}


#endif
