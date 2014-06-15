CC=clang

CFLAGS=-O0 -Wall

OBJECTS = platform.c meminfo.c

all: meminfo shared static

meminfo: 
	$(CC) $(CFLAGS) -o meminfo $(OBJECTS) main.c

#shared:
#	$(CC) $(CFLAGS) -fPIC -o libmeminfo.so $(OBJECTS) 

#static:
#	$(CC) $(CFLAGS) -fPIC -o $(OBJECTS)
#	ar rcs libmeminfo.a *.o

clean:
	rm -f *.o
	rm -f meminfo

