#include <stdio.h>
#include <stdlib.h>

/**
 * main_global - Global variable for task requirements
 */
int main_global = 42;

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
 * print_info - Prints the global variable
 * @n: Value to print
 */
void print_info(int n)
{
	printf("Global Value: %d\n", n);
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
			printf("Loop iteration: %d\n", i);
	}
}

/**
 * main - Entry point for ELF analysis task
 * Return: 0 on success
 */
int main(void)
{
	int *heap_val;

	heap_val = malloc(sizeof(int));
	if (heap_val == NULL)
		return (1);

	process_data(heap_val, main_global);
	print_info(*heap_val);
	run_loop(5);

	free(heap_val);
	return (0);
}
