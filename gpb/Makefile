all: amessagepb_c
	gcc -g -o send amessage_serialize.c amessage.pb-c.c -lprotobuf-c
	gcc -g -o recv amessage_deserialize.c amessage.pb-c.c -lprotobuf-c

amessagepb_c:
	protoc-c  --c_out=. amessage.proto

run:
	./send asd | ./recv

clean:
	rm -rf send recv
	rm -rf amessage.pb-c.c amessage.pb-c.h
