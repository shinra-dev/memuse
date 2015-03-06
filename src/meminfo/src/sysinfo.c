/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "platform.h"
#include "meminfo.h"


int meminfo_system_uptime(runtime_t *uptime)
{
  int ret = MEMINFO_OK;
  *uptime = 0.;
  
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret, FAILURE);
  
  *uptime = (runtime_t) info.uptime;
  #elif OS_WINDOWS
  ULONGLONG tc; // miliseconds
  
    #if defined(_WIN64)
    tc = GetTickCount64();
    #else
    tc = GetTickCount(); // only good up to 49.7 days lol
    #endif
  
  *uptime = (runtime_t) tc/1000;
  #elif OS_MAC
  // https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
  time_t startdate, nowdate;
  struct timeval tv;
  size_t size = sizeof(tv);
  
  ret = sysctlbyname("kern.boottime", &tv, &size, NULL, 0);
  chkret(ret, FAILURE);
  startdate = tv.tv_sec;
  
  time(&nowdate);
  
  *uptime = (runtime_t) nowdate - startdate;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}


