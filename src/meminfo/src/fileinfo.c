/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"

#if OS_NIX
#include <sys/stat.h>
#elif OS_WINDOWS
#include <FileAPI.h>
#endif


int meminfo_filesize(memsize_t *filesize, const char *filename)
{
  int ret = MEMINFO_OK;
  #if OS_NIX
  struct stat sb;
  ret = stat(filename, &sb);
  chkret(ret, FILE_ERROR);
  
  *filesize = (memsize_t) sb.st_size;
  #elif OS_WINDOWS
  LARGE_INTEGER size;
  HANDLE fp = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
  if (fp == INVALID_HANDLE_VALUE)
    return FILE_ERROR;
  
  ret = GetFileSizeEx(fp, &size)
  CloseHandle(fp);
  winchkret(ret, FAILURE);
  
  *filesize = size.QuadPart;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}

