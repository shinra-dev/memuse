CC=clang
CFLAGS=-O0 -Wall

OBJECTS =  cacheinfo.c meminfo.c platform.c print.c process_meminfo.c swapinfo.c

all: meminfo shared static

meminfo: 
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o meminfo

shared:
	$(CC) -c $(CFLAGS) -fPIC $(OBJECTS)
	$(CC) -shared -o libmeminfo.so *.o -lc

static:
	$(CC) -c $(CFLAGS) $(OBJECTS)
	ar rcs libmeminfo.a *.o

clean:
	rm -f *.o
	rm -f meminfo
	rm -f *.a
	rm -f *.so

