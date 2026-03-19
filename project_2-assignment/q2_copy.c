#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

/**
 * copy_syscall - Copy using read/write
 * @src: source path
 * @dest: dest path
 */
void copy_syscall(const char *src, const char *dest)
{
	int s_fd = open(src, O_RDONLY);
	int d_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char buf[4096];
	ssize_t n;

	while ((n = read(s_fd, buf, sizeof(buf))) > 0)
		write(d_fd, buf, n);
	close(s_fd);
	close(d_fd);
}

/**
 * copy_stdio - Copy using fread/fwrite
 * @src: source path
 * @dest: dest path
 */
void copy_stdio(const char *src, const char *dest)
{
	FILE *s = fopen(src, "rb");
	FILE *d = fopen(dest, "wb");
	char buf[4096];
	size_t n;

	while ((n = fread(buf, 1, sizeof(buf), s)) > 0)
		fwrite(buf, 1, n, d);
	fclose(s);
	fclose(d);
}

int main(int ac, char **av)
{
	if (ac < 2) return (1);
	if (av[1][0] == '1') copy_syscall("largefile.bin", "copy1.bin");
	else copy_stdio("largefile.bin", "copy2.bin");
	return (0);
}
