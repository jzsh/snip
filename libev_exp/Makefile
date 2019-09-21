
INCLUDE_DIR = /home/guojz/local/include
LIB_DIR = /home/guojz/local/lib
CFLAGS = -L$(LIB_DIR) -I$(INCLUDE_DIR)

api:api_test.c
	gcc -g $< -lev $(CFLAGS)

sock:
	gcc -g -o server server.c -lev $(CFLAGS)
	gcc -g -o client client.c -lev $(CFLAGS)

.PHONY:clean
clean:
	-rm -rf a.out server client
