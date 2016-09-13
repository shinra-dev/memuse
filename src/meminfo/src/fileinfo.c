/* Copyright (c) 2015-2016, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"

#if OS_NIX
#include <sys/stat.h>
#endif

// PATH_MAX --- should probably do something custom to be more portable
#if OS_LINUX
#include <linux/limits.h>
#elif OS_MAC
#include <sys/syslimits.h>
#elif OS_NIX
#define PATH_MAX 1024
#elif OS_WINDOWS
#define PATH_MAX 4096
#endif


/**
 * @file
 * @brief 
 * Absolute Path
 *
 * @details
 * This function returns the absolute path of a file, given a relative
 * path.  So '~/' turns into '/home/user'.
 *
 * @param relpath
 * Input.  The (possibly relative) path to a file.
 * @param abspath
 * Output.  On successful return, this is set to a pointer to the 
 * absolute path of relpath.  Otherwise, this is set to NULL.
 *
 * @note
 * For *NIX OS's, this uses PATH_MAX and realpath(), which I'm convinced 
 * is actually very unsafe.  But this is portable and easy.  If you
 * know you're prone to large file paths, then you should use
 * something more resiliant.
 * 
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_abspath(const char *relpath, char **abspath)
{
  int ret = MEMINFO_OK;
  
  
#if OS_NIX
  char *ptr;
  *abspath = malloc(PATH_MAX);
  
  ptr = realpath(relpath, *abspath);
  if (ptr == NULL)
  {
    free(abspath);
    return FILE_ERROR;
  }
  
#elif OS_WINDOWS
  DWORD len;
  *abspath = malloc(PATH_MAX);
  
  len = GetFullPathName(relpath, PATH_MAX, abspath, NULL);
  
  if (len > PATH_MAX)
  {
    free(abspath);
    return FAILURE;
  }
  else if (len == 0)
  {
    free(abspath);
    return FILE_ERROR;
  }
  
#else
  return PLATFORM_ERROR;
#endif
  
  return ret;
}



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
 * Input.  The absolute (not relative) path to the file you want to
 * inspect.
 * 
 * @note
 * See meminfo_abspath() for a possible way to get an absolute path
 * from a relative one.
 * 
 * @return
 * The return value indicates the status of the function.
 */
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
  
  ret = GetFileSizeEx(fp, &size);
  CloseHandle(fp);
  winchkret(ret, FAILURE);
  
  *filesize = (memsize_t) size.QuadPart;
#else
  return PLATFORM_ERROR;
#endif
  
  return ret;
}
