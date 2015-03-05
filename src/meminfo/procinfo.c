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
  int ret = MEMINFO_OK;
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
  int ret = MEMINFO_OK;
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


int meminfo_process_utiltime(runtime_t *usr, runtime_t *sys)
{
  int ret = MEMINFO_OK;
  *usr = 0.;
  *sys = 0.;
  
  
  #if OS_LINUX
  ret = read_proc_self_stat(usr, 14);
  chkret(ret);
  ret = read_proc_self_stat(sys, 15);
  chkret(ret);
  
  *usr = (runtime_t) *usr / sysconf(_SC_CLK_TCK);
  *sys = (runtime_t) *sys / sysconf(_SC_CLK_TCK);
  #elif OS_MAC
  struct task_thread_times_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_THREAD_TIMES_INFO, (task_info_t)&info, &info_count);
  
  *usr = (runtime_t) info.user_time; // time_value_t
  *sys = (runtime_t) info.system_time;
  #elif OS_WINDOWS
  FILETIME create_ft, exit_ft, sys_ft, cpu_ft;
  ret = GetProcessTimes(GetCurrentProcess(), &create_ft, &exit_ft, &sys_ft, &cpu_ft); 
  winchkret(ret);
  
  ULARGE_INTEGER sys_uli, usr_uli;
  FILETIMEtoULI(&cpu_ft, &usr_uli);
  FILETIMEtoULI(&sys_ft, &sys_uli);
  
  *usr = (runtime_t) usr_uli.QuadPart * 1e-7;
  *sys = (runtime_t) sys_uli.QuadPart * 1e-7;
  
  return MEMINFO_OK;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}



int meminfo_process_runtime(runtime_t *runtime)
{
  int ret = MEMINFO_OK;
  *runtime = 0.;
  
  
  #if OS_LINUX
  // process runtime = system uptime - (time after boot process started in jiffies / clock ticks per cycle (HZ))
  runtime_t sys_uptime, proc_start_time;
  ret = meminfo_system_uptime(&sys_uptime);
  chkret(ret);
  
  ret = read_proc_self_stat(&proc_start_time, 22);
  chkret(ret);
  
  *runtime = (runtime_t) sys_uptime - (proc_start_time / sysconf(_SC_CLK_TCK));
  #elif OS_WINDOWS
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms683223%28v=vs.85%29.aspx
  FILETIME create_ft, exit_ft, sys_ft, cpu_ft;
  ret = GetProcessTimes(GetCurrentProcess(), &create_ft, &exit_ft, &sys_ft, &cpu_ft); 
  winchkret(ret);
  
  FILETIME nowtime_ft;
  GetSystemTimeAsFileTime(&nowtime_ft);
  
  *runtime = FILETIMEdiff(&nowtime_ft, &create_ft);
  return MEMINFO_OK;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}

