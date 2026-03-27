#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* Global Library State */
char *books[] = {"C Programming", "Linux Kernel", "Assembly x86"};
int reserved[] = {0, 0, 0}; /* 0 = Available, 1 = Reserved */
pthread_mutex_t lib_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * handle_client - Authenticates and manages library reservations
 * @socket_desc: Pointer to the client socket descriptor
 * Return: NULL
 */
void *handle_client(void *socket_desc)
{
	int sock = *(int *)socket_desc;
	char buf[1024], id[1024];
	int choice;
	ssize_t n;

	/* 1. Authentication: Requires ID starting with 'ALU' */
	n = recv(sock, id, 1024, 0);
	if (n <= 0 || strncmp(id, "ALU", 3) != 0)
	{
		send(sock, "AUTH_FAIL", 9, 0);
		close(sock);
		free(socket_desc);
		return (NULL);
	}
	send(sock, "AUTH_SUCCESS", 12, 0);

	/* 2. Book Selection Loop */
	while (recv(sock, buf, 1024, 0) > 0)
	{
		choice = atoi(buf) - 1;
		pthread_mutex_lock(&lib_mutex);
		if (choice >= 0 && choice < 3 && reserved[choice] == 0)
		{
			reserved[choice] = 1;
			send(sock, "RESERVED_SUCCESS", 16, 0);
		}
		else
		{
			send(sock, "ALREADY_TAKEN", 13, 0);
		}
		pthread_mutex_unlock(&lib_mutex);
	}

	close(sock);
	free(socket_desc);
	return (NULL);
}

/**
 * main - Central Library Server entry point
 * Return: (0)
 */
int main(void)
{
	int sfd, *nsock, opt = 1;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);

	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (1);
	listen(sfd, 5);
	printf("Library Server Active on port 8080...\n");

	while (1)
	{
		int csock = accept(sfd, (struct sockaddr *)&addr, &len);
		pthread_t thread;

		nsock = malloc(sizeof(int));
		if (nsock == NULL)
			continue;
		*nsock = csock;
		pthread_create(&thread, NULL, handle_client, (void *)nsock);
		pthread_detach(thread);
	}
	return (0);
}
