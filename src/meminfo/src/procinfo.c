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


#include "meminfo.h"


/**
 * @file
 * @brief 
 * Process Size
 *
 * @details
 * This function looks up the amount of ram used by the current
 * process in bytes.
 *
 * @param size
 * Output, passed by reference.  On successful return, the value
 * is set to the amount of ram used by the current process (in 
 * bytes) available on the system.
 *
 * @notes
 * TODO resident set size, etc.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_process_size(memsize_t *size)
{
  int ret = MEMINFO_OK;
  *size = 0L;
  
  
#if OS_LINUX
  ret = read_proc_file("/proc/self/status", size, "VmRSS:", 6);
  *size *= 1024L;
#elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *size = (memsize_t) pmc.WorkingSetSize;
#elif OS_MAC
  struct task_basic_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &info_count);
  *size = (memsize_t) info.resident_size;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Process Peak Size
 *
 * @details
 * This function looks up the peak amount of ram used by the current
 * process in bytes.
 *
 * @param size
 * Output, passed by reference.  On successful return, the value
 * is set to the maximum amount of ram used by the current process (in 
 * bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_process_peak(memsize_t *peak)
{
  int ret = MEMINFO_OK;
  *peak = 0L;
  
  
#if OS_LINUX
  ret = read_proc_file("/proc/self/status", peak, "VmHWM:", 6);
  *peak *= 1024L;
#elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *peak = (memsize_t) pmc.PeakWorkingSetSize;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}
