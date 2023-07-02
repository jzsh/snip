#define TBB_PREVIEW_GLOBAL_CONTROL 1
#include <iostream>
#include <tbb/task_scheduler_init.h>
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
//     tbb::task_scheduler_init init(2);

    // other tbb init scheduler
    tbb::parallel_for(0, 100, [](int&){
        std::this_thread::sleep_for(10ms);
    });

//     tbb::task_scheduler_init init2(8);

    tbb::task_arena arena(2);
    tbb::task_group group;
    tbb::concurrent_vector<int> numVec;

    cout << "task_arena num: " << arena.max_concurrency() << endl;
    arena.execute([&](){
//     arena.enqueue([&](){
        group.run([&](){
            tbb::parallel_for(0, 100, [&](int& i){
                cout << "run in group" << endl;
                numVec.push_back(i);
                std::this_thread::sleep_for(10ms);
            });
        });
    });

    while(1) {
        if (numVec.size() == 100) break;
    }
    cout << "before wait" << endl;
    group.wait();
    cout << "after wait" << endl;
}

int main()
{
    test2();
}
