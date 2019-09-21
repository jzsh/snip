#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t count_mutex ;
int count;

void *print_msg(void *arg){
    int i=0;
    int thread_num = *((int *)arg);
    printf("Thread %d is starting\n", thread_num);
    if(thread_num == 1) {
        sleep(1);
    } else if(thread_num == 2) {
        sleep(2);
    }

    pthread_mutex_lock(&count_mutex); // 进入关键区域，进程先获得锁
    count++;
    printf("Thread %d: output %d\n", thread_num, count);
    usleep(10000);
    pthread_mutex_unlock(&count_mutex);
}

int main(int argc,char** argv) {
	int th1 = 1;
	int th2 = 2;
    pthread_t id1;
    pthread_t id2;
    pthread_mutex_init(&count_mutex,NULL);
    pthread_create(&id1,NULL,print_msg,(void *)&th1);
    pthread_create(&id2,NULL,print_msg,(void *)&th2);
    pthread_join(id1,NULL); // wait thread terminate, if not main thread exit
    pthread_join(id2,NULL);
    pthread_mutex_destroy(&count_mutex);
    return 1;
}
