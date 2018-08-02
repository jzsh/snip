#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex ;
void *print_msg(void *arg){
    int i=0;
    int thread_num = (int)arg;
    printf("Thread %d is starting\n", thread_num);
    if(thread_num == 1) {
        sleep(1);
    } else if(thread_num == 2) {
        sleep(2);
    }

    pthread_mutex_lock(&mutex);
    for(i=0;i<15;i++){
        printf("Thread %d: output %d\n", thread_num, i);
        usleep(10000);
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc,char** argv) {
    pthread_t id1;
    pthread_t id2;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&id1,NULL,print_msg,(void *)1);
    pthread_create(&id2,NULL,print_msg,(void *)2);
    pthread_join(id1,NULL); // wait thread terminate, if not main thread exit
    pthread_join(id2,NULL);
    pthread_mutex_destroy(&mutex);
    return 1;
}
