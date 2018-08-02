all: libshow.so
	gcc -o cb_demo cb_demo.c -L. -lshow

libshow.so:
	gcc -shared -fPIC show.c -o libshow.so

.PHONY:run clean
run:
	LD_LIBRARY_PATH=. ./cb_demo

clean:
	rm cb_demo *.so
