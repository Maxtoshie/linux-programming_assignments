#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct shared_data - Structure for thread synchronization
 * @belt: Storage array for luggage IDs
 * @count: Current number of items on the belt
 * @loaded: Total number of items loaded by the producer
 * @dispatched: Total number of items removed by the consumer
 * @mutex: Mutex lock for thread-safe access to shared variables
 * @c_space: Condition variable to signal available space on the belt
 * @c_items: Condition variable to signal available items on the belt
 *
 * Description: Holds the shared state for the baggage handling simulation
 */
struct shared_data
{
	int belt[5];
	int count;
	int loaded;
	int dispatched;
	pthread_mutex_t mutex;
	pthread_cond_t c_space;
	pthread_cond_t c_items;
};

/**
 * loader - Producer thread for luggage
 * @arg: Pointer to shared data struct
 * Return: NULL
 */
void *loader(void *arg)
{
	struct shared_data *d = (struct shared_data *)arg;

	while (d->loaded < 20)
	{
		pthread_mutex_lock(&(d->mutex));
		while (d->count == 5)
			pthread_cond_wait(&(d->c_space), &(d->mutex));
		d->belt[d->count++] = ++(d->loaded);
		printf("Loaded luggage ID: %d\n", d->loaded);
		pthread_cond_signal(&(d->c_items));
		pthread_mutex_unlock(&(d->mutex));
		sleep(1);
	}
	return (NULL);
}

/**
 * aircraft - Consumer thread for luggage
 * @arg: Pointer to shared data struct
 * Return: NULL
 */
void *aircraft(void *arg)
{
	struct shared_data *d = (struct shared_data *)arg;

	while (d->dispatched < 20)
	{
		pthread_mutex_lock(&(d->mutex));
		while (d->count == 0)
			pthread_cond_wait(&(d->c_items), &(d->mutex));
		d->count--;
		d->dispatched++;
		printf("Dispatched. Remaining: %d\n", d->count);
		pthread_cond_signal(&(d->c_space));
		pthread_mutex_unlock(&(d->mutex));
		sleep(2);
	}
	return (NULL);
}

/**
 * main - Entry point for producer-consumer baggage task
 * Return: 0
 */
int main(void)
{
	pthread_t t1, t2;
	struct shared_data d = {{0}, 0, 0, 0, PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

	pthread_create(&t1, NULL, loader, &d);
	pthread_create(&t2, NULL, aircraft, &d);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
