CC=gcc
GDB=-g -ggdb

all:
	$(CC) $(GDB) -c *.c
	ar -cvq bin/libvalentina.a *.o

clear:
	rm bin/*.a
	rm *.o
