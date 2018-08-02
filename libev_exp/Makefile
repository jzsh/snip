
exp1:exp1.c
	gcc -g $< -lev

sock:
	gcc -g -o server server.c -lev
	gcc -g -o client client.c -lev

.PHONY:clean
clean:
	-rm -rf a.out server client
