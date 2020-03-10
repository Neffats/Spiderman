#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	int sockfd = 0, connfd = 0, n = 0;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t client_len;	

	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
	}

	if (listen(sockfd, 10) == -1) {
		perror("ERROR on listen");
	}
	client_len = sizeof(client_addr);

	while(1) {
		connfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
		if (connfd < 0) {
			printf("failed to accept new connection\n");
			continue;
		}

		bzero(buffer, 256);
		n = read(connfd, buffer, 255);
		if (n < 0) {
			printf("failed to read from connection fd\n");
			continue;
		}
		printf("%s\n", buffer);
		close(connfd);		
	}

}
