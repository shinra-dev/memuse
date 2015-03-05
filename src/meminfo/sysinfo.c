/*
  Copyright (c) 2015, Schmidt
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


int meminfo_system_uptime(runtime_t *uptime)
{
  int ret = 0;
  *uptime = 0.;
  
  
  #if OS_LINUX
  struct sysinfo info;
  ret = sysinfo(&info);
  
  chkret(ret);
  
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
  chkret(ret);
  startdate = tv.tv_sec;
  
  time(&nowdate);
  
  *uptime = (runtime_t) nowdate - startdate;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}


