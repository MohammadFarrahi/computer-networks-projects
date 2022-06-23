#include "Router.hpp"

Router::Router(int port, int receiver_port, int queue_size)
{
	this->port = port;
	this->receiver_port;
	this->queue_size = queue_size;

	this->port_map[receiver_port] = htons(receiver_port);
}

void Router::start()
{
	setup_socket();

	thread incoming_thread(&Router::process_incoming, this);
	thread outgoing_thread(&Router::process_outgoing, this);

	incoming_thread.join();
	outgoing_thread.join();
}

void Router::process_incoming()
{
	struct sockaddr_in incomming_addr;
	fd_set read_fds;
	int nbytes;
	socklen_t incomming_addr_len = sizeof(incomming_addr);

	char buffer[SEGMENT_SIZE];

	while (true)
	{
		FD_ZERO(&read_fds);
		FD_SET(sockfd, &read_fds);

		int n = select(sockfd + 1, &read_fds, 0, 0, 0);

		if (n < 0)
		{
			cerr << "ERROR Server : select()" << endl;
			close(sockfd);
			exit(1);
		}

		if (FD_ISSET(sockfd, &read_fds))
		{
			this->queue_mutex.lock();
			memset(buffer, 0, SEGMENT_SIZE);
			nbytes = recvfrom(sockfd, buffer, SEGMENT_SIZE, 0, (struct sockaddr *)&incomming_addr, &incomming_addr_len);
			if (nbytes < 0)
			{
				cerr << "ERROR in recvfrom()" << endl;
				close(sockfd);
				exit(1);
			}

			auto segment = new Segment();
			segment->deserialize(buffer);

			update_port_map(segment->get_src_port(), incomming_addr.sin_port);

			add_to_queue(segment);
			cout << "Segment with seq_num " << segment->get_seq_num() << " received from " << ntohs(incomming_addr.sin_port) << endl;
			this->queue_mutex.unlock();
		}
		FD_CLR(sockfd, &read_fds);
	}
}

void Router::process_outgoing()
{
	while (true)
	{
		this->queue_mutex.lock();
		if (this->segment_queue.size() == 0)
		{
			this->queue_mutex.unlock();
			continue;
		}

		auto segment = this->segment_queue.front();
		this->segment_queue.pop();

		// send with socket
		char buffer[SEGMENT_SIZE];
		memset(buffer, 0, SEGMENT_SIZE);
		segment->serialize(buffer);

		struct sockaddr_in send_addr;
		memset(&send_addr, 0, sizeof(send_addr));
		send_addr.sin_family = AF_INET;
		send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		send_addr.sin_port = this->port_map[segment->get_dst_port()];

		

		auto nbytes = sendto(this->sockfd, buffer, strlen(buffer), MSG_CONFIRM,
												(const struct sockaddr *)&send_addr, sizeof(send_addr));

		cout << "Segment with seq_num " << segment->get_seq_num() << " sent to " << ntohs(send_addr.sin_port) << endl;
		cout << "size sent:  " << nbytes << endl;
		// printf("\n\n%s\n\n\n", buffer);
		this->queue_mutex.unlock();
	}
}

void Router::setup_socket()
{
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cerr << "socket creation failed" << endl;
		exit(EXIT_FAILURE);
	}

	memset(&send_addr, 0, sizeof(send_addr));
	this->send_addr.sin_family = AF_INET;
	this->send_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(&routeraddr, 0, sizeof(routeraddr));

	// Filling router information
	routeraddr.sin_family = AF_INET; // IPv4
	routeraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	routeraddr.sin_port = htons(port);

	// Bind the socket with the router address
	if (bind(sockfd, (const struct sockaddr *)&routeraddr,
					 sizeof(routeraddr)) < 0)
	{
		cerr << "bind failed" << endl;
		exit(EXIT_FAILURE);
	}
}

void Router::update_port_map(int application_port, int os_port)
{
	if (application_port == receiver_port)
		return;
	if (port_map.find(application_port) == port_map.end())
		port_map[application_port] = os_port;
}

void Router::add_to_queue(Segment *segment)
{
	if (segment_queue.size() == queue_size)
		return;

	segment_queue.push(segment);
}

int main(int argc, char *argv[])
{
	auto router_port = stoi(argv[1]);
	auto receiver_port = stoi(argv[2]);

	Router router(router_port, receiver_port, 10000);

	router.start();
}