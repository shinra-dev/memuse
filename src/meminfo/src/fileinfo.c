/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"

#if OS_NIX
#include <limits.h>
#include <sys/stat.h>
#elif OS_WINDOWS
#include <FileAPI.h>
#endif

/**
 * @file
 * @brief 
 * File Size
 *
 * @details
 * This function looks up the size of a file in bytes.  It does so
 * without scanning the file (just reports whatever the filesystem
 * believes).
 *
 * @param filesize
 * Output, passed by reference.  On successful return, the value
 * is set to the file size (in bytes) of the file pointed to by
 * 'filename'.
 * @param filename
 * Input.  The path to the file you want to inspect.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_filesize(memsize_t *filesize, const char *filename)
{
  int ret = MEMINFO_OK;
  
  
  #if OS_NIX
  char *resolved_path[PATH_MAX];
  char *rpret;
  
  rpret = realpath(filename, resolved_path);
  if (rpret == NULL)
    return FILE_ERROR;
  
  struct stat sb;
  ret = stat(resolved_path, &sb);
  chkret(ret, FILE_ERROR);
  
  *filesize = (memsize_t) sb.st_size;
  #elif OS_WINDOWS
  // TODO GetFullPathName
  
  LARGE_INTEGER size;
  HANDLE fp = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
  if (fp == INVALID_HANDLE_VALUE)
    return FILE_ERROR;
  
  ret = GetFileSizeEx(fp, &size)
  CloseHandle(fp);
  winchkret(ret, FAILURE);
  
  *filesize = (memsize_t) size.QuadPart;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}

