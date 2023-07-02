#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>
#include <tbb/task_group.h>
#include <tbb/global_control.h>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>
#include <thread>
#include <stdarg.h>

using namespace std;

void print(const char* format, ...)
{
    printf("[%ld]", pthread_self());
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    printf("\n");
    va_end(ap);
}

void test2()
{
    tbb::global_control gc(tbb::global_control::max_allowed_parallelism, 2);

    // other tbb init scheduler
//     tbb::parallel_for(0, 100, [](int&){
//         std::this_thread::sleep_for(10ms);
//     });
    // tbb::global_control gc(tbb::global_control::max_allowed_parallelism, 8);

    tbb::task_arena arena(1);
    tbb::task_group group;
    tbb::concurrent_vector<int> numVec;
    tbb::concurrent_unordered_set<size_t> pidSet;

    print("task_arena num: %d", arena.max_concurrency());
    bool running = false;
    arena.execute([&](){    // lamda run in master thread
//     arena.enqueue([&](){ // lamda run in worker thread
        running = true;
        print("run in task arena");
        group.run([&](){
            print("run in task group");
            tbb::parallel_for(0, 100, [&](int& i){
                print("run in group");
                numVec.push_back(i);
                std::this_thread::sleep_for(10ms);
                pidSet.insert(pthread_self());
            });
            print("out of task group");
        });
        print("out of task arena");
    });

//     while(1) {
//         if (numVec.size() == 100) break;
//     }
    while(!running) {
        std::this_thread::sleep_for(100ms);
    }
    print("before wait");
    group.wait();
    print("after wait");
}

int main()
{
    test2();
}
