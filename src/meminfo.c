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
  
  return -1;
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
  if (ret !=0 )
    ret = 0;
  else
    ret = -1;
  
  (*mem)[MEMUNIT] = 1.0;
  
  (*mem)[TOTALRAM] = ((double) status.ullTotalPhys);
  (*mem)[FREERAM] = ((double) status.ullAvailPhys);
  (*mem)[TOTALPAGE] = ((double) status.ullTotalPageFile);
  (*mem)[FREEPAGE] = ((double) status.ullAvailPageFile);
  
  
  return ret;
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
