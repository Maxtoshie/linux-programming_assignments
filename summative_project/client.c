#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 * main - Library student client entry point
 * Return: (0) on success, (1) on error
 */
int main(void)
{
	int sock;
	struct sockaddr_in server;
	char id[1024], choice[1024], response[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		return (1);

	printf("Enter Library ID: ");
	scanf("%s", id);
	send(sock, id, strlen(id), 0);

	recv(sock, response, 1024, 0);
	if (strncmp(response, "AUTH_SUCCESS", 12) != 0)
	{
		printf("Authentication Failed. Session closed.\n");
		close(sock);
		return (1);
	}

	printf("Auth Successful!\nBooks: 1. C, 2. Linux, 3. x86\nEnter choice (1-3): ");
	scanf("%s", choice);
	send(sock, choice, strlen(choice), 0);

	memset(response, 0, 1024);
	recv(sock, response, 1024, 0);
	printf("Server Response: %s\n", response);

	printf("Session closed. Goodbye, %s\n", id);
	close(sock);
	return (0);
}
