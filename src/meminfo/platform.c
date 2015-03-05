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


#if OS_LINUX

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
        sscanf(tmp, "%*s%ld", &value);
        break;
      }
    }
    
    fclose(fp);
    free(tmp);
    
    if (value != FAILURE)
    {
      *val = value;
      return 0;
    }
  }
  
  return FAILURE;
}

int read_proc_self_stat(uptime_t *val, const int n)
{
  int i;
  int spaces = 0, last_space = 0;
  char *line = NULL;
  size_t linelen = 0;
  memsize_t value = FAILURE;
  char *end;
  
  *val = 0L;
  
  FILE* fp = fopen("/proc/self/stat", "r");
  if (fp == NULL)
    return FAILURE;
  
  linelen = getline(&line, &linelen, fp);
  
  for (i=0; i<linelen; i++)
  {
    if (line[i] == ' ')
    {
      spaces++;
      
      if (spaces == n)
        *val = strtoull(line+last_space, &end, 10);
      else
        last_space = i;
    }
  }
  
  
  free(line);
  fclose(fp);
  
  return 0;
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




#elif OS_WINDOWS

void FILETIMEtoULI(FILETIME *ft, ULARGE_INTEGER *uli)
{
  uli->LowPart   = ft->dwLowDateTime;
  uli->HighPart  = ft->dwHighDateTime;
}

// ft1 - ft2
uptime_t FILETIMEdiff(FILETIME *ft1, FILETIME *ft2)
{
  uptime_t ut;
  
  ULARGE_INTEGER uli1, uli2;
  
  FILETIMEtoULI(ft1, &uli1);
  FILETIMEtoULI(ft2, &uli2);
  
  ut = (uptime_t) (uli1.QuadPart - uli2.QuadPart) * 1e-7;
  
  return ut;
}

#endif

