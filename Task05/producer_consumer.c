#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5
#define ITEMS 20
#define THREADS 4

int buffer[SIZE];
int in = 0, out = 0;
int sum = 0, consumed = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < ITEMS / THREADS; i++)
    {
        int item = id * 5 + i + 1;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
    (void)arg;

    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        out = (out + 1) % SIZE;

        if (item == -1)
        {
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            break;
        }

        sum += item;
        consumed++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

int main()
{
    pthread_t producers[THREADS], consumers[THREADS];
    int ids[THREADS];

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREADS; i++)
    {
        ids[i] = i;
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(producers[i], NULL);

    for (int i = 0; i < THREADS; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = -1;
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(consumers[i], NULL);

    printf("Producer-Consumer Simulation\n");
    printf("Producers: 4\n");
    printf("Consumers: 4\n");
    printf("Total items consumed: %d\n", consumed);
    printf("Sum of consumed items: %d\n", sum);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
