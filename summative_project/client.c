#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
	int sock;
	struct sockaddr_in server;
	char message[1024], server_reply[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		return (1);

	recv(sock, server_reply, 1024, 0);
	printf("%s", server_reply);

	scanf("%s", message);
	send(sock, message, strlen(message), 0);

	memset(server_reply, 0, 1024);
	recv(sock, server_reply, 1024, 0);
	printf("%s", server_reply);

	close(sock);
	return (0);
}
