
ob:subject.o main.o observer.h
	g++ -o $@ $^ -g -O0

%.o: %.cpp
	g++ -c -o $@ $^ -g -O0

clean:
	rm -f *.o
