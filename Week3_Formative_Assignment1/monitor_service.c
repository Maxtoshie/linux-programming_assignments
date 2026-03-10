#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * handle_signal - process received unix signals
 * @sig: the signal number received
 */
void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nMonitor Service shutting down safely.\n");
		exit(0);
	}
	else if (sig == SIGUSR1)
	{
		printf("System status requested by administrator.\n");
	}
	else if (sig == SIGTERM)
	{
		printf("Emergency shutdown signal received.\n");
		exit(0);
	}
}

/**
 * main - background service simulator
 *
 * Return: 0
 */
int main(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGUSR1, handle_signal);
	signal(SIGTERM, handle_signal);

	while (1)
	{
		printf("[Monitor Service] System running normally...\n");
		sleep(5);
	}

	return (0);
}
