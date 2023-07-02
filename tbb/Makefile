THREAD = -lpthread
#TBBLIB = -ltbb \
		 -L/home/gjz/depot/tbb/lib/ \
		 -I/home/gjz/depot/tbb/include/

#TBBLIB = -ltbb \
		 -L/home/gjz/depot/tbb_2019/lib \
		 -I/home/gjz/depot/tbb_2019/include
TBBLIB = -ltbb \
		 -L/home/gjz/depot/tbb_2018/lib \
		 -I/home/gjz/depot/tbb_2018/include

#ONETBBLIB = -ltbb \
		 -L/home/gjz/depot/tbb/lib \
		 -I/home/gjz/depot/tbb/include
ONETBBLIB = -ltbb_debug \
		 -L/home/gjz/depot/onetbb_debug/lib \
		 -I/home/gjz/depot/onetbb_debug/include

task_scheduler_init: task_scheduler_init.cpp
	g++ $^ -o $@ $(THREAD) -g -O0 $(TBBLIB)

task_arena: task_arena.cpp
	g++ $^ -o $@ $(THREAD) -g -O0 $(ONETBBLIB)
