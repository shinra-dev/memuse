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


// Returns
#define chkret(ret) if(ret)return(ret)

#define MEMUSE_OK 0
#define FAILURE -1
#define PLATFORM_ERROR -10


typedef uint64_t memsize_t;
typedef uint32_t cachesize_t;

// cacheinfo.c
int meminfo_cachesize(cachesize_t *totalcache, const unsigned int level);
int meminfo_cachelinesize(cachesize_t *totalcache);

// getpid.c
uint32_t meminfo_getpid();

// print.c
int meminfo_putval(memsize_t val);

// process_meminfo.c
int meminfo_process_size(memsize_t *size);
int meminfo_process_peak(memsize_t *peak);

// raminfo.c
int meminfo_totalram(memsize_t *totalram);
int meminfo_freeram(memsize_t *freeram);
int meminfo_bufferram(memsize_t *bufferram);
int meminfo_cachedram(memsize_t *cachedram);

// swapinfo.c
int meminfo_totalswap(memsize_t *totalswap);
int meminfo_freeswap(memsize_t *freeswap);
int meminfo_cachedswap(memsize_t *cachedswap);



#endif
