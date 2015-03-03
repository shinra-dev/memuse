/*
  Copyright (c) 2014-2015, Schmidt
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


#include "platform.h"
#include "meminfo.h"


/* 
 *           Mem sizes
 */

int meminfo_process_size(memsize_t *size)
{
  int ret = 0;
  *size = 0L;
  
  
  #if OS_LINUX
  ret = read_proc_file("/proc/self/status", size, "VmSize:", 7);
  *size *= 1024L;
  #elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *size = (memsize_t)pmc.WorkingSetSize;
  #elif OS_MAC
  struct task_basic_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &info_count);
  *size = info.resident_size;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}


int meminfo_process_peak(memsize_t *peak)
{
  int ret = 0;
  *peak = 0L;
  
  
  #if OS_LINUX
  ret = read_proc_file("/proc/self/status", peak, "VmPeak:", 7);
  *peak *= 1024L;
  #elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *peak = (memsize_t)pmc.PeakWorkingSetSize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}



/* 
 *           Proc times
 */

// http://man7.org/linux/man-pages/man5/proc.5.html

int meminfo_process_utiltime(time_t *usr, time_t *sys)
{
  int ret = 0;
  *peak = 0L;
  
  
  #if OS_LINUX
  // proc self stat, fields 14 and 15 (maybe also want 16 and 17 for forking?)
  #elif OS_MAC
  struct task_thread_times_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_THREAD_TIMES_INFO, (task_info_t)&info, &info_count);
  
  *usr = (time_t) info.user_time; // time_value_t
  *sys = (time_t) info.system_time;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}



int meminfo_process_uptime(time_t *uptime)
{
  int ret = 0;
  *peak = 0L;
  
  
  #if OS_LINUX
  // proc self stat, field 22
  #elif OS_WINDOWS
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms683223%28v=vs.85%29.aspx
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}



