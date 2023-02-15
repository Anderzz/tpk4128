#include <stdio.h>
#include <pthread.h>

/*
Two threads execute concurrently, each with its own local variable. The global variable is shared between the threads.
The global variable should in theory be 200 0000, but it is not. This is because the global variable is not protected
by a mutex, so the threads can access it at the same time and read an outdated version of it. It's caused by race conditions.
*/

int global_variable = 0;

void *thread_function(void *arg) {
    int *local_variable_ptr = (int *)arg;
    int local_variable = *local_variable_ptr;

    for (int i = 0; i < 1000000; i++) {
        local_variable++;
        global_variable++;
    }

    *local_variable_ptr = local_variable;
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int local_variable1 = 0, local_variable2 = 0;

    pthread_create(&thread1, NULL, thread_function, (void *)&local_variable1);
    pthread_create(&thread2, NULL, thread_function, (void *)&local_variable2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Local variable 1: %d\n", local_variable1);
    printf("Local variable 2: %d\n", local_variable2);
    printf("Global variable: %d\n", global_variable);

    return 0;
}
