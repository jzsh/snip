run:demo
	@export LD_LIBRARY_PATH=.; \
	./demo
demo:libtest.so libprintf.a
	$(CC) main.c -L. -ltest -lprintf -o demo
libtest.so:
	$(CC) test.c -fPIC -shared -o libtest.so
libprintf.a:printf1.o printf2.o
	ar -rsv libprintf.a printf1.o printf2.o
%.o:%.c
	$(CC) -O -c $^
clean:
	-rm -rf demo *.o *.so *.a
