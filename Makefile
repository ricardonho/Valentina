CC=gcc
GDB=-g -ggdb

all:
	$(CC) $(GDB) -c src/*.c
	ar -cvq bin/libvalentina.a *.o

clear:
	rm bin/*.a
	rm *.o
