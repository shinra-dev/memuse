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


#include <stdint.h>
#include "platform.h"
#include "meminfo.h"

#if OS_WINDOWS
#include <PsAPI.h>
int meminfo_getpid();
#endif


// http://msdn.microsoft.com/en-us/library/windows/desktop/ms682050%28v=vs.85%29.aspx

int meminfo_process_size(uint64_t *size)
{
  int ret;
  
  #if OS_LINUX
  ret = read_proc_file("/proc/self/status", size, "VmSize:", 7);
  *size *= 1024L;
  #elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *size = (uint64_t)pmc.WorkingSetSize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}


int meminfo_process_peak(uint64_t *peak)
{
  int ret;
  
  #if OS_LINUX
  ret = read_proc_file("/proc/self/status", peak, "VmPeak:", 7);
  *peak *= 1024L;
  #elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *peak = (uint64_t)pmc.PeakWorkingSetSize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}


