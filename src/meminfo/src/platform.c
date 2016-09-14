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


// for getline()
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif

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
