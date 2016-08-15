/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"


#if OS_LINUX

#include <inttypes.h>

int read_proc_file(const char *file, memsize_t *val, char *field, int fieldlen)
{
  size_t len = 0;
  char *tmp;
  memsize_t value = FAILURE;
  
  *val = 0L;
  
  FILE* fp = fopen(file, "r");
  
  if (fp != NULL)
  {
    while (getline(&tmp, &len, fp) >= 0)
    {
      if (strncmp(tmp, field, fieldlen) == 0)
      {
        sscanf(tmp, "%*s%" SCNu64, &value);
        break;
      }
    }
    
    fclose(fp);
    free(tmp);
    
    if (value != FAILURE)
    {
      *val = value;
      return MEMINFO_OK;
    }
  }
  
  return FAILURE;
}



#elif OS_MAC || OS_FREEBSD

int sysctl_mib(char *name, int *mib, size_t *mibsize){
  return sysctlnametomib(name,mib,mibsize);
}

int sysctlmib_val(int *mib, size_t mibsize, void *data, size_t *datasize){
  return sysctl(mib, mibsize+1, data, datasize, NULL, 0);
}

int sysctl_val(char *name, memsize_t *val)
{
  int ret;
  size_t vallen;
  vallen = sizeof(*val);
  
  ret = sysctlbyname(name, val, &vallen, NULL, 0);
  
  return ret;
}


#endif
