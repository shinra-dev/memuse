#include "memuse.h"



#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define chkret(ret) if(ret)return(ret)


int get_cached(double *memcached, char *field, int fieldlen)
{
  int tmplen = 1024 * sizeof(char);;
  char *tmp;
  long value = -1L;
  
  memcached[0] = 0;
  
  FILE* fp = fopen("/proc/meminfo", "r");
  
  if (fp != NULL)
  {
    tmp = (char*) malloc(tmplen);
    
    while (getline(&tmp, &tmplen, fp) >= 0)
    {
      if (strncmp(tmp, field, fieldlen) != 0)
        continue;
      
      sscanf(tmp, "%*s%ld", &value);
      break;
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

// FIXME use sysctl
int get_meminfo(double **mem)
{
  
}



// --------------------------------------------------------
#elif OS_WINDOWS

#include <Windows.h>
// idk lol


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
  
  (*mem)[MEMCACHED] = MISSING;
  (*mem)[BUFFERRAM] = MISSING;
  (*mem)[TOTALSWAP] = MISSING;
  (*mem)[FREESWAP] = MISSING;
  
  return(0);
}



// --------------------------------------------------------
#else


int get_meminfo(double **mem)
{
  return PLATFORM_ERROR;
}


#endif
