#include <stdio.h>
#include <stdlib.h>

/**
 * process_data - Performs a write operation to allocated memory
 * @ptr: Pointer to allocated memory
 * @val: Value to write
 */
void process_data(int *ptr, int val)
{
	if (ptr != NULL)
		*ptr = val * 2;
}

/**
 * print_info - Prints the calculated value
 * @n: Value to print
 */
void print_info(int n)
{
	printf("Calculated Value: %d\n", n);
}

/**
 * run_loop - Implements a simple loop
 * @limit: Number of iterations
 */
void run_loop(int limit)
{
	int i;

	for (i = 0; i < limit; i++)
	{
		if (i % 2 == 0)
			printf("Iteration: %d\n", i);
	}
}

/**
 * main - Entry point for ELF analysis task
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int *heap_val;
	int local_val = 42;

	heap_val = malloc(sizeof(int));
	if (heap_val == NULL)
		return (1);

	process_data(heap_val, local_val);
	print_info(*heap_val);
	run_loop(5);

	free(heap_val);
	return (0);
}
