#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point for the data sync simulator
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	FILE *src, *dest;
	char buffer[1024];
	size_t bytes;

	if (argc < 3)
	{
		printf("Usage: %s <source> <destination>\n", argv[0]);
		return (1);
	}

	src = fopen(argv[1], "rb");
	if (src == NULL)
		return (1);

	dest = fopen(argv[2], "wb");
	if (dest == NULL)
	{
		fclose(src);
		return (1);
	}

	while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
		fwrite(buffer, 1, bytes, dest);

	fclose(src);
	fclose(dest);
	return (0);
}
