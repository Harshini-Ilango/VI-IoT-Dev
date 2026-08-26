#include <stdio.h>
#include <pthread.h>

#define LOOPS 10000000

int counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg)
{
    for (int i = 0; i < LOOPS; i++)
    {
        pthread_mutex_lock(&lock);

        counter++;

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, worker, NULL);
    pthread_create(&thread2, NULL, worker, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter = %d\n", counter);

    pthread_mutex_destroy(&lock);

    return 0;
}
