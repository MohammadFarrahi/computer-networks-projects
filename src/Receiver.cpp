#include "Receiver.hpp"

Receiver::Receiver(int port)
{
	this->port = port;
}

void Receiver::start()
{
	setup_socket();

	char incoming_buffer[SEGMENT_SIZE];
	char outgoing_buffer[SEGMENT_SIZE];

	while (true)
	{
		memset(&cliaddr, 0, sizeof(cliaddr));
		memset(incoming_buffer, 0, sizeof(incoming_buffer));
		socklen_t cliaddr_len = sizeof(cliaddr);
		recvfrom(sockfd, incoming_buffer, SEGMENT_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr,
						 &cliaddr_len);

		int client_port = cliaddr.sin_port;

		if (clients.find(client_port) == clients.end())
		{
			clients[client_port] = new ClientReceiver(client_port, this->port);
		}

		memset(outgoing_buffer, 0, sizeof(outgoing_buffer));
		auto success = clients[client_port]->process_packet(incoming_buffer, outgoing_buffer);
		if (success)
		{
			sendto(sockfd, outgoing_buffer, strlen(outgoing_buffer),
						 MSG_CONFIRM, (struct sockaddr *)&cliaddr, cliaddr_len);
		}
	}
}

void Receiver::setup_socket()
{
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cerr << "socket creation failed" << endl;
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
					 sizeof(servaddr)) < 0)
	{
		cerr << "bind failed" << endl;
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	auto server_port = stoi(argv[1]);
	Receiver receiver(server_port);

	receiver.start();
}