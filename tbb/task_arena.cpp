#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>
#include <tbb/task_group.h>
#include <tbb/global_control.h>
#include <tbb/concurrent_vector.h>
#include <thread>

using namespace std;

void test2()
{
    tbb::global_control gc(tbb::global_control::max_allowed_parallelism, 2);

    // other tbb init scheduler
//     tbb::parallel_for(0, 100, [](int&){
//         std::this_thread::sleep_for(10ms);
//     });
    // tbb::global_control gc(tbb::global_control::max_allowed_parallelism, 8);

    tbb::task_arena arena(2);
    tbb::task_group group;
    tbb::concurrent_vector<int> numVec;

    cout << "task_arena num: " << arena.max_concurrency() << endl;
    bool running = false;
    arena.execute([&](){
//     arena.enqueue([&](){
        running = true;
        cout << "run in task arena" << endl;
        group.run([&](){
            tbb::parallel_for(0, 100, [&](int& i){
                cout << "run in group" << endl;
                numVec.push_back(i);
                std::this_thread::sleep_for(10ms);
            });
        });
        cout << "out of task arena" << endl;
    });

//     while(1) {
//         if (numVec.size() == 100) break;
//     }
    while(!running) {
        std::this_thread::sleep_for(100ms);
    }
    cout << "before wait" << endl;
    group.wait();
    cout << "after wait" << endl;
}

int main()
{
    test2();
}
