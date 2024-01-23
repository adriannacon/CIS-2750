CC = clang
CFLAGS = -Wall -std=c99 -pedantic -g

all: test

clean:
	rm -f *.o *.so phylib test

phylib.o: phylib.c phylib.h
	$(CC) $(CFLAGS) -c phylib.c -fPIC -o phylib.o

libphylib.so: phylib.o
	$(CC) -shared -o libphylib.so phylib.o

test: A1test1.c phylib.h libphylib.so
	$(CC) $(CFLAGS) -o test A1test1.c -L. -lphylib -lm
