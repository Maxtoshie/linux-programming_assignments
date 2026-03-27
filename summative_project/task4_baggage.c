#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define CAPACITY 5

int belt[CAPACITY];
int count = 0;
int total_loaded = 0;
int total_dispatched = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_items = PTHREAD_COND_INITIALIZER;

void *loader(void *arg)
{
	while (total_loaded < 20)
	{
		pthread_mutex_lock(&mutex);
		while (count == CAPACITY)
			pthread_cond_wait(&cond_space, &mutex);

		belt[count++] = ++total_loaded;
		printf("Loaded luggage ID: %d (Size: %d)\n", total_loaded, count);

		pthread_cond_signal(&cond_items);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	return NULL;
}

void *aircraft(void *arg)
{
	while (total_dispatched < 20)
	{
		pthread_mutex_lock(&mutex);
		while (count == 0)
			pthread_cond_wait(&cond_items, &mutex);

		int item = belt[--count];
		total_dispatched++;
		printf("Dispatched luggage ID: %d (Remaining: %d)\n", item, count);

		pthread_cond_signal(&cond_space);
		pthread_mutex_unlock(&mutex);
		sleep(4);
	}
	return NULL;
}

int main(void)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, loader, NULL);
	pthread_create(&t2, NULL, aircraft, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
