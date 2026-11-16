#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define CAMERAS 64

int next_camera = 0;
int processed = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void process_camera(int id)
{
    struct timespec delay = {0, 10000000};
    nanosleep(&delay, NULL);

    pthread_mutex_lock(&lock);
    processed++;
    pthread_mutex_unlock(&lock);
}

void *camera_thread(void *arg)
{
    int id = *(int *)arg;
    process_camera(id);
    return NULL;
}

void *worker_thread(void *arg)
{
    (void)arg;

    while (1)
    {
        pthread_mutex_lock(&lock);

        if (next_camera >= CAMERAS)
        {
            pthread_mutex_unlock(&lock);
            break;
        }

        int id = next_camera++;
        pthread_mutex_unlock(&lock);

        process_camera(id);
    }

    return NULL;
}

void run_individual_threads()
{
    pthread_t threads[CAMERAS];
    int ids[CAMERAS];

    next_camera = 0;
    processed = 0;

    for (int i = 0; i < CAMERAS; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, camera_thread, &ids[i]);
    }

    for (int i = 0; i < CAMERAS; i++)
        pthread_join(threads[i], NULL);

    printf("One thread per camera: %d cameras processed\n", processed);
}

void run_thread_pool(int workers)
{
    pthread_t threads[16];

    next_camera = 0;
    processed = 0;

    for (int i = 0; i < workers; i++)
        pthread_create(&threads[i], NULL, worker_thread, NULL);

    for (int i = 0; i < workers; i++)
        pthread_join(threads[i], NULL);

    printf("Thread pool (%d workers): %d cameras processed\n",
           workers, processed);
}

int counter = 0;

void *unsafe_increment(void *arg)
{
    (void)arg;

    for (int i = 0; i < 100000; i++)
        counter++;

    return NULL;
}

void *safe_increment(void *arg)
{
    (void)arg;

    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    printf("TRAFFIC CAMERA THREAD DEMONSTRATION\n\n");

    run_individual_threads();
    run_thread_pool(4);
    run_thread_pool(8);
    run_thread_pool(16);

    pthread_t t1, t2;

    counter = 0;
    pthread_create(&t1, NULL, unsafe_increment, NULL);
    pthread_create(&t2, NULL, unsafe_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nCounter without mutex: %d (expected 200000)\n", counter);

    counter = 0;
    pthread_create(&t1, NULL, safe_increment, NULL);
    pthread_create(&t2, NULL, safe_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter with mutex: %d (expected 200000)\n", counter);

    pthread_mutex_destroy(&lock);
    return 0;
}
