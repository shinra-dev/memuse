/*  Copyright (c) 2015-2016 Drew Schmidt
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


// for realpath()
#include "os.h"

#if !OS_WINDOWS
#include "conf.h"
#endif


#include "meminfo.h"

#if OS_NIX
#include <sys/stat.h>
#endif

#if OS_LINUX
#include <linux/limits.h>
#define MEMUSE_PATH_MAX PATH_MAX
#elif OS_MAC || OS_FREEBSD
#include <sys/syslimits.h>
#define MEMUSE_PATH_MAX PATH_MAX
#elif OS_NIX
#define MEMUSE_PATH_MAX 1024
#elif OS_WINDOWS
#define MEMUSE_PATH_MAX 4096
#endif


/**
 * @file
 * @brief 
 * Absolute Path
 *
 * @details
 * This function returns the absolute path of a file, given a relative
 * path.  So '../whatever' becomes '/path/to/wherever/'.
 *
 * @param relpath
 * Input.  The (possibly relative) path to a file.
 * @param abspath
 * Output.  On successful return, this is set to a pointer to the 
 * absolute path of relpath.  Otherwise, this is set to NULL.
 *
 * @note
 * For *NIX OS's, this uses MEMUSE_PATH_MAX and realpath(), which I'm convinced 
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
  *abspath = malloc(MEMUSE_PATH_MAX);
  
  ptr = realpath(relpath, *abspath);
  if (ptr == NULL)
  {
    free(abspath);
    return FILE_ERROR;
  }
  
#elif OS_WINDOWS
  DWORD len;
  *abspath = malloc(MEMUSE_PATH_MAX);
  len = GetFullPathName(relpath, MEMUSE_PATH_MAX, (LPTSTR) *abspath, NULL);
  
  if (len > MEMUSE_PATH_MAX)
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
