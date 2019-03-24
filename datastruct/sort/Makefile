CFLAGS+=-Wall -Werror -g -O0 -I.. -I.

all: sort.c main.c util.o
	gcc $^ $(CFLAGS)

util.o:../util.c
	gcc -c -o util.o ../util.c

clean:
	rm -rf *.o a.out
