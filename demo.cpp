#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <map>
#include <string.h>


using namespace std;

int main()
{
  auto sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in routeraddr;
  memset(&routeraddr, 0, sizeof(routeraddr));

	// Filling router information
	routeraddr.sin_family = AF_INET; // IPv4
	routeraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	routeraddr.sin_port = htons(8084);

  if (bind(sockfd, (const struct sockaddr *)&routeraddr,
					 sizeof(routeraddr)) < 0)
	{
		cerr << "bind failed" << endl;
		exit(EXIT_FAILURE);
	}

  struct sockaddr_in to;
  memset(&to, 0, sizeof(to));

	// Filling router information
	to.sin_family = AF_INET; // IPv4
	to.sin_addr.s_addr = inet_addr("127.0.0.1");
	to.sin_port = htons(8081);

  char buffer[2048] = "08082080810000000000./README.md";

  sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, 
  (const struct sockaddr *)&to, sizeof(to));

  return 0;
}