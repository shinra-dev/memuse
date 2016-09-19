/*  Copyright (c) 2014-2016 Drew Schmidt
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


#ifndef __MEMINFO_OS__
#define __MEMINFO_OS__


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

// For testing only!
// #undef OS_LINUX
// #define OS_LINUX 0
// #undef OS_NIX
// #define OS_NIX 1

#endif
