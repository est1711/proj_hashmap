CC = gcc
CFLAGS = -Wall

all:exec

hashmap.o : hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c hashmap.c -o hashmap.o

listechainee.o : listechainee.c listechainee.h
	$(CC) $(CFLAGS) -c listechainee.c -o listechainee.o


abr.o : abr.c abr.h
	$(CC) $(CFLAGS)  -c abr.c -o abr.o


lib.so: hashmap.o listechainee.o abr.o
	$(CC) -shared -o lib.so hashmap.o listechainee.o abr.o



exec: main.o hashmap.o abr.o listechainee.o lib.so
	$(CC) $(CFLAGS) -o exec main.o hashmap.o abr.o listechainee.o -L. -l:lib.so

clean:
	rm -f exec
	rm -f lib.so
	rm -f *.o
