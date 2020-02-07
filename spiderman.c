#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define INADDR_ANY (u_int32_t)0x00000000

int main() {
	int s, c, b;
	struct sockaddr_in sa;
	FILE *client;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}
	
	bzero(&sa, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(13);
	if (INADDR_ANY)
		sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr*) &sa, sizeof sa) < 0) {
		perror("bind");
		return 2;
	}

	switch (fork()) {
		case -1:
			perror("fork");
			return 3;
			break;
		default:
			close(s);
			return 0;
			break;
		case 0:
			break;
	}

	listen(s, 4);

	for(;;) {
		b = sizeof sa;

		if ((c = accept(s, (struct sockaddr*)&sa, &b)) < 0) {
			perror("accept");
			return 4;
		}
		if ((client = fdopen(c, "w")) == NULL) {
			perror("client fdopen");
			return 5;
		}
		
		fprintf(client, "Hello there...");
		fclose(client);
	}
}

