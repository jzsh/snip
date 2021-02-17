CPPFLAGS = -std=c++11 -g -O0


all:Singletion lazy_no_safe

Singletion:Singletion.cpp
	g++ -o $@  $(CPPFLAGS) Singletion.cpp

lazy_no_safe:SingletionLazy.cpp
	g++ -o $@ $(CPPFLAGS)  SingletionLazy.cpp -lpthread

clean:
	rm -f lazy_no_safe Singletion
