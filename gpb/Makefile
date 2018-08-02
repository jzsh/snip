all:
	gcc -g -o send amessage_serialize.c amessage.pb-c.c -lprotobuf-c
	gcc -g -o recv amessage_deserialize.c amessage.pb-c.c -lprotobuf-c

run:
	./send asd | ./recv
