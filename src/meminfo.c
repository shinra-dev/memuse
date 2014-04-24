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



#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define chkret(ret) if(ret)return(ret)

int get_cached(double *memcached, char *field, int fieldlen)
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
  
  return -1;
}

int get_meminfo(double **mem)
{
  int ret;
  double memcached;
  
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  // cached
  ret = get_cached(&memcached, "Cached", 6);
  
  chkret(ret);
  (*mem)[MEMCACHED] = memcached;
  
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
#elif (OS_BSD || OS_MAC)

#include <sys/types.h>
#include <sys/sysctl.h>

int get_meminfo(double **mem)
{
  
  
  int mib [] = { CTL_HW, HW_MEMSIZE };
  int64_t value = 0;
  size_t length = sizeof(value);
  
  if(-1 == sysctl(mib, 2, &value, &length, NULL, 0))
    // An error occurred
  
  mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
  vm_statistics_data_t vmstat;
  if(KERN_SUCCESS != host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count))
    // An error occurred
  
  double total = vmstat.wire_count + vmstat.active_count + vmstat.inactive_count + vmstat.free_count;
  double wired = vmstat.wire_count / total;
  double active = vmstat.active_count / total;
  double inactive = vmstat.inactive_count / total;
  double free = vmstat.free_count / total;
  
  
  
}



// --------------------------------------------------------
#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int get_meminfo(double **mem)
{
  int ret;
  
  MEMORYSTATUSEX status;
  
  status.dwLength = sizeof(status);
  
  ret = GlobalMemoryStatusEx(&status);
  
  // IN BYTES !
  
  
  // Total ram
  status.ullTotalPhys
  
  // Free
  statex.ullAvailPhys
  
  // Page total
  statex.ullTotalPageFile
  
  // Free paging
  statex.ullAvailPageFile
  
  // VM total
  statex.ullTotalVirtual
  
  // VM free
  statex.ullAvailVirtual
  
  
  return status.ullTotalPhys;
}


// --------------------------------------------------------
#elif OS_NIX // Misc nix's

#include <unistd.h>

int get_meminfo(double **mem)
{
  long npages, pagesize, freepages;
  
  *mem = malloc(MEMLEN * sizeof(*mem));
  
  npages = sysconf(_SC_PHYS_PAGES);
  pagesize = sysconf(_SC_PAGESIZE);
  freepages = sysconf( _SC_AVPHYS_PAGES);
  
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
