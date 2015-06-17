/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#ifndef __MEMINFO__
#define __MEMINFO__


#include <stdint.h>
#include "platform.h"


#define chkret(ret,val) if(ret)return(val)
#if OS_WINDOWS
// Windows.h functions return non-zero if successful IN SPITEFUL DEFIANCE OF THE FUCKING C STANDARD
#define winchkret(ret,val) if(!ret)return(val)
#endif

#define MEMINFO_OK       0
#define FAILURE         -1   // internal error
#define FILE_ERROR      -2   // bad file
#define CACHE_ERROR     -3   // impossible cache value
#define PLATFORM_ERROR  -10  // platform not supported


typedef uint64_t memsize_t;
typedef uint32_t cachesize_t;

// cacheinfo.c
int meminfo_cachesize(cachesize_t *totalcache, const unsigned int level);
int meminfo_cachelinesize(cachesize_t *totalcache);

// fileinfo.c
int meminfo_abspath(const char *relpath, char **abspath);
int meminfo_filesize(memsize_t *filesize, const char *filename);

// getpid.c
uint32_t meminfo_getpid();

// platform.c
#if OS_LINUX
int read_proc_file(const char* file, uint64_t *val, char *field, int fieldlen);
#elif OS_MAC
int sysctl_val(char *name, uint64_t *val);
#elif OS_FREEBSD
int sysctl_mib(char *name, int *mib, size_t *mibsize);
int sysctlmib_val(int *mib, size_t mibsize, void *data, size_t *datasize);
int sysctl_val(char *name, uint64_t *val);
#endif

// print.c
int meminfo_print_memval(memsize_t val);

// procinfo.c
int meminfo_process_size(memsize_t *size);
int meminfo_process_peak(memsize_t *peak);

// raminfo.c
int meminfo_totalram(memsize_t *totalram);
int meminfo_freeram(memsize_t *freeram);
int meminfo_bufferram(memsize_t *bufferram);
int meminfo_cachedram(memsize_t *cachedram);

// swapinfo.c
int meminfo_totalswap(memsize_t *totalswap);
int meminfo_freeswap(memsize_t *freeswap);
int meminfo_cachedswap(memsize_t *cachedswap);


#endif

