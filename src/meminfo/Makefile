CC=clang
CFLAGS=-O0 -w

ifeq ($(OS),Windows_NT)
  CC=gcc
  LDFLAGS=-lpsapi
  TKLIB="-L/opt/tcl/lib -ltk -ltcl"
  TKINC="-I/opt/tcl/include"
endif


OBJECTS = cacheinfo.c fileinfo.c platform.c print.c procinfo.c raminfo.c swapinfo.c sysinfo.c

all: meminfo shared static

meminfo:
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o meminfo $(LDFLAGS)

shared:
	$(CC) -c $(CFLAGS) -fPIC $(OBJECTS) $(LDFLAGS)
	$(CC) -shared -o libmeminfo.so *.o -lc

static:
	$(CC) -c $(CFLAGS) $(OBJECTS) $(LDFLAGS)
	ar rcs libmeminfo.a *.o

clean:
	rm -f *.o
	rm -f meminfo
	rm -f *.a
	rm -f *.so

