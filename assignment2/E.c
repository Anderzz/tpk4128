#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5

// declare the philosophers (threads) and the forks (mutexes)

pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher_logic_deadlock(void *arg)
{
    int id = *(int *)arg;
    int left = id;                           // left fork
    int right = (id + 1) % NUM_PHILOSOPHERS; // right fork

    printf("Philosopher %d wants to eat\n", id);

    // pick up the right fork
    pthread_mutex_lock(&forks[right]);
    printf("Philosopher %d picked up fork %d \n", id, right);

    sleep(1); // ensures a deadlock

    // pick up the left fork
    pthread_mutex_lock(&forks[left]);
    printf("Philosopher %d picked up fork %d \n", id, left);

    printf("Philosopher %d is eating \n", id);
    sleep(1); // eat

    // put down the forks
    pthread_mutex_unlock(&forks[left]);
    printf("Philosopher %d put down fork %d \n", id, left);
    pthread_mutex_unlock(&forks[right]);
    printf("Philosopher %d put down fork %d \n", id, right);

    printf("Philosopher %d is done eating \n", id);

    return NULL;
}

void *philosopher_logic_no_deadlock(void *arg)
{
    int id = *(int *)arg;
    int left = id;                           // left fork
    int right = (id + 1) % NUM_PHILOSOPHERS; // right fork

    printf("Philosopher %d wants to eat\n", id);

    // pick up the lower numbered fork first
    if (left < right)
    { // left first
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up fork %d \n", id, left);
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up fork %d \n", id, right);
    }
    else
    { // right first
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up fork %d \n", id, right);
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up fork %d \n", id, left);
    }

    printf("Philosopher %d is eating \n", id);
    sleep(1); // eat

    // put down the forks
    pthread_mutex_unlock(&forks[left]);
    printf("Philosopher %d put down fork %d \n", id, left);
    pthread_mutex_unlock(&forks[right]);
    printf("Philosopher %d put down fork %d \n", id, right);

    printf("Philosopher %d is done eating \n", id);

    return NULL;
}

int main()
{

    int i;
    int ids[NUM_PHILOSOPHERS];

    bool deadlock = false;

    // initialize the forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    // create the philosophers
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        if (deadlock)
        {
            pthread_create(&philosophers[i], NULL, philosopher_logic_deadlock, &ids[i]);
        }
        else
        {
            pthread_create(&philosophers[i], NULL, philosopher_logic_no_deadlock, &ids[i]);
        }
    }

    // wait for the philosophers to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // destroy the forks

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
