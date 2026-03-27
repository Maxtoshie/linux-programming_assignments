#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct shared_data - shared data for baggage synchronization
 * @belt: storage array for luggage IDs
 * @count: current number of items on the belt
 * @loaded: total number of items loaded
 * @dispatched: total number of items removed
 * @mutex: mutex lock for safe access
 * @c_space: condition for available space
 * @c_items: condition for available items
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
 * monitor - Monitoring thread that runs every 5 seconds
 * @arg: Pointer to shared data struct
 * Return: NULL
 */
void *monitor(void *arg)
{
	struct shared_data *d = (struct shared_data *)arg;

	while (d->dispatched < 20)
	{
		sleep(5);
		pthread_mutex_lock(&(d->mutex));
		printf("\n[MONITOR] Total Loaded: %d | Dispatched: %d | On Belt: %d\n",
			d->loaded, d->dispatched, d->count);
		pthread_mutex_unlock(&(d->mutex));
	}
	return (NULL);
}

/**
 * loader - Producer thread for luggage (2s delay)
 * @arg: Pointer to shared data struct
 * Return: NULL
 */
void *loader(void *arg)
{
	struct shared_data *d = (struct shared_data *)arg;

	while (d->loaded < 20)
	{
		sleep(2);
		pthread_mutex_lock(&(d->mutex));
		while (d->count == 5)
			pthread_cond_wait(&(d->c_space), &(d->mutex));
		d->belt[d->count++] = ++(d->loaded);
		printf("Loader: Luggage ID %d on belt (Size: %d)\n", d->loaded, d->count);
		pthread_cond_signal(&(d->c_items));
		pthread_mutex_unlock(&(d->mutex));
	}
	return (NULL);
}

/**
 * aircraft - Consumer thread for luggage (4s delay)
 * @arg: Pointer to shared data struct
 * Return: NULL
 */
void *aircraft(void *arg)
{
	struct shared_data *d = (struct shared_data *)arg;

	while (d->dispatched < 20)
	{
		sleep(4);
		pthread_mutex_lock(&(d->mutex));
		while (d->count == 0)
			pthread_cond_wait(&(d->c_items), &(d->mutex));
		d->count--;
		d->dispatched++;
		printf("Aircraft: Luggage loaded (Belt Size: %d)\n", d->count);
		pthread_cond_signal(&(d->c_space));
		pthread_mutex_unlock(&(d->mutex));
	}
	return (NULL);
}

/**
 * main - Entry point for baggage handling simulation
 * Return: (0)
 */
int main(void)
{
	pthread_t t1, t2, t3;
	struct shared_data d = {{0}, 0, 0, 0, PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

	pthread_create(&t1, NULL, loader, &d);
	pthread_create(&t2, NULL, aircraft, &d);
	pthread_create(&t3, NULL, monitor, &d);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	return (0);
}
