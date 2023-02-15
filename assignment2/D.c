#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int running = 1;
int var1 = 0;
int var2 = 0;
// declare a mutex
pthread_mutex_t mutex;

void *thread1_function(void *arg){
    while (running){
        // lock mutex
        pthread_mutex_lock(&mutex);
        var1++;
        var2 = var1;
        // unlock mutex
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *thread2_function(void *arg){
    for (int i = 0; i < 20; i++){
        // lock mutex
        pthread_mutex_lock(&mutex);
        printf("i = %d, number 1 is %d, number 2 is %d, difference is %d\n", i+1 ,var1, var2, var1 - var2);
        // unlock mutex
        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }
    running = 0;
    return NULL;
}
int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);



    return 0;
}