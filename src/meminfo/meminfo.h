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

// Magic numbers
#define chkret(ret) if(ret)return(ret)

#define MEMUSE_OK 0
#define FAILURE -1
#define PLATFORM_ERROR -10


// cacheinfo.c
int meminfo_cachesize(uint32_t *totalcache, const unsigned int level);
int meminfo_cachelinesize(uint16_t *totalcache);

// getpid.c
uint32_t meminfo_getpid();

// meminfo.c
int meminfo_totalram(uint64_t *totalram);
int meminfo_freeram(uint64_t *freeram);
int meminfo_bufferram(uint64_t *bufferram);
int meminfo_cachedram(uint64_t *cachedram);
int meminfo_totalswap(uint64_t *totalswap);
int meminfo_freeswap(uint64_t *freeswap);
int meminfo_cachedswap(uint64_t *cachedswap);

// print.c
int meminfo_putval(uint64_t val);

// process_meminfo.c
int meminfo_process_size(uint64_t *size);
int meminfo_process_peak(uint64_t *peak);


#endif
