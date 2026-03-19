#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * main - Implements a pipeline ps aux | grep root and captures output
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int pipefd[2];
	pid_t pid1, pid2;
	int file_fd;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		char *args[] = {"ps", "aux", NULL};
		execvp(args[0], args);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		char *args[] = {"grep", "root", NULL};
		execvp(args[0], args);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	printf("Pipeline finished. Results saved to output.txt\n");
	return (0);
}
