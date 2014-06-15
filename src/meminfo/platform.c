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

#include "meminfo.h"


#if OS_LINUX

int read_proc_meminfo(uint64_t *val, char *field, int fieldlen)
{
  int tmplen = 1024 * sizeof(char);
  char *tmp;
  uint64_t value = -1L;
  
  val[0] = 0L;
  
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
      val[0] = value * 1024L;
      return 0;
    }
  }
  
  return FAILURE;
}


#elif OS_MAC || OS_FREEBSD

int sysctl_val(char *name, uint64_t *val)
{
  int ret;
  uint64_t oldp;
  size_t oldlenp;
  oldlenp = sizeof(oldp);
  
  ret = sysctlbyname(name, &oldp, &oldlenp, NULL, 0);
  
  *val = (uint64_t) oldp;
  
  return ret;
}

#endif


