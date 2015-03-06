/* Copyright (c) 2014, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include <stdint.h>
#include "meminfo.h"


uint32_t meminfo_getpid()
{
  #if OS_WINDOWS
  DWORD pid = GetCurrentProcessId();
  #elif OS_NIX
  uint32_t pid = getpid();
  #else
  return PLATFORM_ERROR;
  #endif
  
  return (uint32_t) pid;
}

