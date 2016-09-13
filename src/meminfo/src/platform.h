/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#ifndef __MEMINFO_PLATFORM__
#define __MEMINFO_PLATFORM__


// "portability"
//#define CYGWIN_OR_MINGW (defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__) || defined(__CYGWIN32__))
#define OS_LINUX (defined(__gnu_linux__) || defined(__linux__) || defined(__linux))
#define OS_WINDOWS (defined(__WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__) || defined(__TOS_WIN__) || defined(__WINNT) || defined(__WINNT__))
#define OS_MAC (defined(__APPLE__) && defined(__MACH__))
#define OS_FREEBSD (defined(__FreeBSD__))
#define OS_BSD (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__))
#define OS_SOLARIS (defined(__sun) || defined(sun))
#define OS_HURD (defined(__GNU__) || defined(__gnu_hurd__)) // why the hell not
#define OS_NIX (OS_BSD || OS_HURD || OS_LINUX || OS_MAC || OS_SOLARIS)

#include <stdint.h>


#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#elif OS_MAC

#include <stdlib.h>

#include <mach/vm_statistics.h>
#include <mach/mach.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>


#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Psapi.h>

typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);


#elif OS_FREEBSD

#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>



#elif OS_NIX

#include <stdlib.h> 
#include <unistd.h>

#endif


#endif
