// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT1	 8080
#define PORT2	 8081
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd1, sockfd2;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr1, cliaddr1;
    struct sockaddr_in servaddr2, cliaddr2;
		
	// Creating socket file descriptor
	if ((sockfd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

    if ((sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr1, 0, sizeof(servaddr1));
	memset(&cliaddr1, 0, sizeof(cliaddr1));

    memset(&servaddr2, 0, sizeof(servaddr2));
	memset(&cliaddr2, 0, sizeof(cliaddr2));
		
	// Filling server information
	servaddr1.sin_family = AF_INET; // IPv4
	servaddr1.sin_addr.s_addr = INADDR_ANY;
	servaddr1.sin_port = htons(PORT1);

    servaddr2.sin_family = AF_INET; // IPv4
	servaddr2.sin_addr.s_addr = INADDR_ANY;
	servaddr2.sin_port = htons(PORT2);
		
	if (bind(sockfd1, (const struct sockaddr *)&servaddr1, sizeof(servaddr1)) < 0)
	{
		perror("bind1 failed");
		exit(EXIT_FAILURE);
	}

	// if (bind(sockfd2, (const struct sockaddr *)&servaddr2, sizeof(servaddr2)) < 0)
	// {
	// 	perror("bind2 failed");
	// 	exit(EXIT_FAILURE);
	// }

	socklen_t len1,len2, n;
	
	len1 = sizeof(cliaddr1); //len1 is value/result
    len2 = sizeof(cliaddr2); //len1 is value/result
	buffer[2048] = '\0';

	while(true) {
		recvfrom(sockfd1, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr1,
				(socklen_t*)&len1);

		printf("%s\n", buffer);
	}
	
	

	// sendto(sockfd2, buffer, strlen(buffer),
	// 	MSG_CONFIRM, (const struct sockaddr *) &servaddr2,
	// 		len2);

    // recvfrom(sockfd2, buffer, MAXLINE,
	// 			MSG_WAITALL, ( struct sockaddr *) &servaddr2,
	// 			(socklen_t*)&len2);

	// printf("%s\n", buffer);

	// sendto(sockfd1, buffer, strlen(buffer),
	// 	MSG_CONFIRM, (const struct sockaddr *) &cliaddr1,
	// 		len1);
		
	return 0;
}
