#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LIMIT 200000
#define THREADS 16

int total_primes = 0;
pthread_mutex_t mutex;

/**
 * is_prime - checks if number is prime
 * @n: number
 * Return: 1 if prime, 0 otherwise
 */
int is_prime(int n)
{
	int i;
	if (n < 2) return (0);
	for (i = 2; i * i <= n; i++)
		if (n % i == 0) return (0);
	return (1);
}

/**
 * count_segment - Thread worker function
 * @arg: pointer to start of range
 */
void *count_segment(void *arg)
{
	int start = *((int *)arg);
	int end = start + (LIMIT / THREADS);
	int i, count = 0;

	for (i = start; i < end; i++)
		if (is_prime(i)) count++;
	
	pthread_mutex_lock(&mutex);
	total_primes += count;
	pthread_mutex_unlock(&mutex);
	free(arg);
	return (NULL);
}

int main(void)
{
	pthread_t t[THREADS];
	int i;

	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < THREADS; i++)
	{
		int *start = malloc(sizeof(int));
		*start = i * (LIMIT / THREADS) + 1;
		pthread_create(&t[i], NULL, count_segment, start);
	}
	for (i = 0; i < THREADS; i++) pthread_join(t[i], NULL);
	
	printf("The synchronized total number of prime numbers between 1 and 200,000 is %d\n", total_primes);
	pthread_mutex_destroy(&mutex);
	return (0);
}
