#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
 * send_handler - Allows the server user to type a message to the client
 * @sock_desc: Pointer to the socket descriptor
 * Return: NULL
 */
void *send_handler(void *sock_desc)
{
	int sock = *(int *)sock_desc;
	char message[1024];

	while (fgets(message, 1024, stdin))
	{
		send(sock, message, strlen(message), 0);
	}
	return (NULL);
}

/**
 * handle_client - Receives messages and spawns the sender thread
 * @socket_desc: Pointer to the client socket descriptor
 * Return: NULL
 */
void *handle_client(void *socket_desc)
{
	int sock = *(int *)socket_desc;
	char buffer[1024];
	int read_size;
	pthread_t sthread;

	pthread_create(&sthread, NULL, send_handler, (void *)&sock);
	pthread_detach(sthread);

	while ((read_size = recv(sock, buffer, 1024, 0)) > 0)
	{
		buffer[read_size] = '\0';
		printf("\n[Student]: %s> ", buffer);
		fflush(stdout);
	}

	close(sock);
	free(socket_desc);
	return (NULL);
}

/**
 * main - Entry point for the bi-directional library server
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	int server_fd, *new_sock;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int opt = 1;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);

	if (bind(server_fd, (struct sockaddr *)&address, (socklen_t)addrlen) < 0)
		return (1);
	listen(server_fd, 5);

	printf("Server started. You can type to connected clients.\n");
	while (1)
	{
		int client_sock = accept(server_fd, (struct sockaddr *)&address,
					 (socklen_t *)&addrlen);
		pthread_t rthread;

		new_sock = malloc(sizeof(int));
		*new_sock = client_sock;
		pthread_create(&rthread, NULL, handle_client, (void *)new_sock);
		pthread_detach(rthread);
	}
	return (0);
}
