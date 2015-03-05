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


#ifndef __MEMINFO__
#define __MEMINFO__


#include <stdint.h>
#include "platform.h"


// Returns
#if OS_WINDOWS
#define chkret(ret) if(!ret)return(ret)
#else
#define chkret(ret) if(ret)return(ret)
#endif

#define MEMUSE_OK       0
#define FAILURE         -1
#define FILE_ERROR      -2
#define PLATFORM_ERROR  -10


typedef uint64_t memsize_t;
typedef uint32_t cachesize_t;
typedef uint64_t uptime_t;

// cacheinfo.c
int meminfo_cachesize(cachesize_t *totalcache, const unsigned int level);
int meminfo_cachelinesize(cachesize_t *totalcache);

// fileinfo.c
int meminfo_filesize(memsize_t *filesize, const char *filename);

// getpid.c
uint32_t meminfo_getpid();

// print.c
int meminfo_putval(memsize_t val);

// procinfo.c
int meminfo_process_size(memsize_t *size);
int meminfo_process_peak(memsize_t *peak);

int meminfo_process_uptime(uptime_t *uptime);

// raminfo.c
int meminfo_totalram(memsize_t *totalram);
int meminfo_freeram(memsize_t *freeram);
int meminfo_bufferram(memsize_t *bufferram);
int meminfo_cachedram(memsize_t *cachedram);

// swapinfo.c
int meminfo_totalswap(memsize_t *totalswap);
int meminfo_freeswap(memsize_t *freeswap);
int meminfo_cachedswap(memsize_t *cachedswap);

// sysinfo.c
int meminfo_system_uptime(uptime_t *uptime);


#endif

