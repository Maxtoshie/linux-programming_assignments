#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - triggers specific system calls for monitoring
 *
 * Return: 0 on success
 */
int main(void)
{
	int fd;
	char buf[20] = "Log entry\n";
	char read_buf[20];

	/* File Creation & Writing */
	fd = open("trace_log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != -1)
	{
		write(fd, buf, 10);
		close(fd);
	}

	/* Reading */
	fd = open("trace_log.txt", O_RDONLY);
	if (fd != -1)
	{
		read(fd, read_buf, 10);
		close(fd);
	}

	return (0);
}
