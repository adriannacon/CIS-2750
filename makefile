CC = clang
CFLAGS = -Wall -std=c99 -pedantic

all:  phylib

clean:  
	rm -f *.o *.so phylib

libphylib.so: phylib.o
	$(CC) phylib.o -shared -o libphylib.so

phylib.o:  phylib.c phylib.h
	$(CC) $(CFLAGS) -c phylib.c -fPIC -o phylib.o

main.o:  main.c phylib.h
	$(CC) $(FLAGS) -c main.c -o main.o

phylib:  main.o libphylib.so
	$(CC) main.o -L. -lphylib -o phylib
