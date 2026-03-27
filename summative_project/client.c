#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

/**
 * receive_handler - Thread to listen for server messages
 * @sock_desc: Pointer to the socket descriptor
 * Return: NULL
 */
void *receive_handler(void *sock_desc)
{
	int sock = *(int *)sock_desc;
	char server_reply[1024];
	int read_size;

	while ((read_size = recv(sock, server_reply, 1024, 0)) > 0)
	{
		server_reply[read_size] = '\0';
		printf("\n%s\n> ", server_reply);
		fflush(stdout);
	}
	return (NULL);
}

/**
 * main - Entry point for library student client
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	int sock;
	struct sockaddr_in server;
	char message[1024];
	pthread_t recv_thread;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		return (1);

	pthread_create(&recv_thread, NULL, receive_handler, (void *)&sock);
	pthread_detach(recv_thread);

	printf("Connected. Type your ID or messages:\n> ");
	while (fgets(message, 1024, stdin))
	{
		send(sock, message, strlen(message), 0);
		printf("> ");
		fflush(stdout);
	}

	close(sock);
	return (0);
}
