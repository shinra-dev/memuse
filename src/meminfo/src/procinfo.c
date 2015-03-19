/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "platform.h"
#include "meminfo.h"


/* 
 *           Mem sizes
 */


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
  ret = read_proc_file("/proc/self/status", size, "VmSize:", 7);
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
  return PLATFORM_ERROR;
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
  ret = read_proc_file("/proc/self/status", peak, "VmPeak:", 7);
  *peak *= 1024L;
  #elif OS_WINDOWS
  PROCESS_MEMORY_COUNTERS pmc;
  
  GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
  *peak = (memsize_t) pmc.PeakWorkingSetSize;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}

