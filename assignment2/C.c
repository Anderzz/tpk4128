#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define _BSD_SOURCE

const int NUM_THREADS = 5;
const int NUM_RESOURCES = 3;

sem_t semaphore;


void *thread_function(void *arg){
    int thread_id = *(int*)arg;
    int resource_num = thread_id % NUM_RESOURCES;

    // wait for semaphore
    printf("Thread %d is waiting for resource %d...\n", thread_id, resource_num);
    sem_wait(&semaphore);

    // use resource
    printf("Thread %d is using resource %d...\n", thread_id, resource_num);
    usleep(1000000);

    // release resource
    printf("Thread %d is releasing resource %d...\n", thread_id, resource_num);
    sem_post(&semaphore);

    return NULL;
}





int main(){

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    sem_init(&semaphore, 0, NUM_RESOURCES);

    // create threads
    for (int i = 0; i < NUM_THREADS; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }


    // wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    return 0;
}