CC=clang
CFLAGS=-O0 -w

ifeq ($(OS),Windows_NT)
  CC=gcc
  LDFLAGS=-lpsapi
  TKLIB="-L/opt/tcl/lib -ltk -ltcl"
  TKINC="-I/opt/tcl/include"
endif


OBJECTS = src/cacheinfo.c src/fileinfo.c src/platform.c src/print.c \
					src/procinfo.c src/raminfo.c src/swapinfo.c src/sysinfo.c

all: meminfo shared static

meminfo:
	$(CC) $(CFLAGS) $(OBJECTS) src/main.c -o meminfo $(LDFLAGS)

shared:
	$(CC) -c $(CFLAGS) -fPIC $(OBJECTS) $(LDFLAGS)
	$(CC) -shared -o libmeminfo.so *.o -lc

static:
	$(CC) -c $(CFLAGS) $(OBJECTS) $(LDFLAGS)
	ar rcs libmeminfo.a *.o

documentation:
	doxygen meminfo.conf

clean:
	rm -f *.o src/*.o
	rm -f *.a
	rm -f *.so
	rm -f meminfo

