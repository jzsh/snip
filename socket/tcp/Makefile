all:server client
server:server.c
	gcc -o server server.c -g
client:client.c
	gcc -o client client.c -g
send:
	dd if=/dev/urandom of=send.dat count=1024 bs=1024
clean:
	rm -rf server client send.dat recv.dat
