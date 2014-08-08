/*
  Copyright (c) 2014, Schmidt
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


#ifndef __MEMINFO_PLATFORM__
#define __MEMINFO_PLATFORM__


// "portability"
#define OS_LINUX (defined(__gnu_linux__) || defined(__linux__) || defined(__linux) || defined(linux))

#define OS_WINDOWS (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__))

#define OS_MAC ((defined(__APPLE__) && defined(__MACH__)) || macintosh || Macintosh)

#define OS_FREEBSD defined(__FreeBSD__)
#define OS_BSD (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__))
#define OS_SOLARIS (defined(__sun) || defined(sun))
#define OS_HURD (defined(__GNU__) || defined(__gnu_hurd__)) // why the hell not

#define OS_NIX (defined(OS_BSD) || defined(OS_HURD) || defined(OS_LINUX) || defined(OS_MAC) || defined(OS_SOLARIS))



#include <stdint.h>


#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int read_proc_file(const char* file, uint64_t *val, char *field, int fieldlen);


#elif OS_MAC

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>

int sysctl_val(char *name, uint64_t *val);


#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>



#elif OS_FREEBSD

#include <unistd.h>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>

int sysctl_mib(char *name, int *mib, size_t *mibsize);
int sysctlmib_val(int *mib, size_t mibsize, void *data, size_t *datasize);
int sysctl_val(char *name, uint64_t *val);


#elif OS_NIX

#include <unistd.h>

#endif


#endif
