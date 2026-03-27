#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
 * handle_client - Process individual student requests
 * @socket_desc: Pointer to the client socket descriptor
 * Return: NULL
 */
void *handle_client(void *socket_desc)
{
	int sock = *(int *)socket_desc;
	char buffer[1024] = {0};
	char *welcome = "ALU Digital Library: Enter Student ID to access: ";
	char *access_ok = "Access Granted. Welcome to the Library!\n";
	char *access_denied = "Access Denied. Invalid ID.\n";

	send(sock, welcome, strlen(welcome), 0);
	recv(sock, buffer, 1024, 0);

	/* Mock validation: Only IDs starting with 'ALU' are granted access */
	if (strncmp(buffer, "ALU", 3) == 0)
		send(sock, access_ok, strlen(access_ok), 0);
	else
		send(sock, access_denied, strlen(access_denied), 0);

	close(sock);
	free(socket_desc);
	return (NULL);
}

int main(void)
{
	int server_fd, *new_sock;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);

	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	listen(server_fd, 5);

	printf("Library Server started on port 8080...\n");

	while (1)
	{
		int client_sock = accept(server_fd, (struct sockaddr *)&address,
					 (socklen_t *)&addrlen);
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;

		pthread_create(&sniffer_thread, NULL, handle_client, (void *)new_sock);
		pthread_detach(sniffer_thread);
	}
	return (0);
}
