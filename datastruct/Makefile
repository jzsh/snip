CFLAGS+=-Wall -g -O0
all:sort.o util.o main.o
	gcc -o a.out sort.o util.o main.o
main.o:
	gcc -c main.c $(CFLAGS)
sort.o:sort.c
	gcc -c sort.c $(CFLAGS)
util.o:util.c
	gcc -c util.c $(CFLAGS)
clean:
	rm -rf *.o a.out
