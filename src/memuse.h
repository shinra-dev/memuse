#ifndef __R_MEMINFO__
#define __R_MEMINFO__


// "portability"
#define OS_LINUX (defined(__gnu_linux__) || defined(__linux__) || defined(__linux) || defined(linux))

#define OS_WINDOWS (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__))

#define OS_MAC ((defined(__APPLE__) && defined(__MACH__)) || macintosh || Macintosh)

#define OS_FREEBSD defined(__FreeBSD__)
#define OS_BSD (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__))
#define OS_SOLARIS (defined(__sun) || defined(sun))
#define OS_HURD (defined(__GNU__) || defined(__gnu_hurd__)) // why the hell not

#define OS_NIX (defined(OS_BSD) || defined(OS_HURD) || defined(OS_LINUX) || defined(OS_MAC) || defined(OS_SOLARIS))


// FIXME in case I'm dumb enough to leave these in on accident, 
// I'm using these for testing
//#define OS_LINUX 0
//#define OS_NIX 1


#if OS_LINUX
  #define MEMLEN 8
  
  #define TOTALRAM 0
  #define FREERAM 1
  #define BUFFERRAM 2
  #define MEMCACHED 3
  #define TOTALSWAP 4
  #define FREESWAP 5
  #define SWAPCACHED 6
  #define MEMUNIT 7
#elif OS_MAC
  #define MEMLEN 5
  
  #define TOTALRAM 0
  #define FREERAM 1
  #define TOTALSWAP 2
  #define FREESWAP 3
  #define MEMUNIT 4
#elif OS_WINDOWS
  #define MEMLEN 5
  
  #define TOTALRAM 0
  #define FREERAM 1
  #define TOTALPAGE 2
  #define FREEPAGE 3
  #define MEMUNIT 4
#elif OS_FREEBSD
  #define MEMLEN 4
  
  #define TOTALRAM 0
  #define FREERAM 1
  #define TOTALSWAP 2
  #define MEMUNIT 3
#elif OS_NIX
  #define MEMLEN 3
  
  #define TOTALRAM 0
  #define FREERAM 1
  #define MEMUNIT 2
#endif


// Magic numbers
#define FAILURE -1
#define PLATFORM_ERROR -10


// prototypes
int get_meminfo(double **mem);


#endif
