#include "Router.hpp"

Router::Router(int port, int receiver_port, int queue_size, int drop_rate, bool red_option)
{
	this->port = port;
	this->receiver_port;
	this->QUEUE_SIZE = queue_size;
	this->DROP_RATE = drop_rate;

	this->port_map[receiver_port] = htons(receiver_port);
	this->is_red_enabled = red_option;
	srand(time(NULL));
}

void Router::start()
{
	setup_socket();

	qTime = time(NULL);
	cout << minThreshold << " thresholds " << maxThreshold << endl;
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

			if (is_random_drop())
				cout << "Segment with seq_num:ack " << segment->get_seq_num() << ":" << segment->get_acknowlegment() << " random dropped" << endl;

			else if (this->is_red_enabled && segment->get_src_port() != this->receiver_port && is_random_early_detection_drop())
				cout << "Segment with seq_num:ack " << segment->get_seq_num() << ":" << segment->get_acknowlegment() << " red dropped" << endl;
			else
			{
				add_to_queue(segment);
				cout << "Segment with seq_num:ack " << segment->get_seq_num() << ":" << segment->get_acknowlegment() << " received from " << ntohs(incomming_addr.sin_port) << endl;
			}
			this->queue_mutex.unlock();
		}
		FD_CLR(sockfd, &read_fds);
	}
}

bool Router::is_random_early_detection_drop()
{
	cout << "\n\nRED: *********START******************************" << endl;
	bool result = false;
	// Calculating queue length
	if (segment_queue.size() == 0)
	{
		double m = (time(NULL) - qTime);
		avg = pow((1 - wq), m) * avg;

		// Update qTime, since the queue is now empty
		qTime = time(NULL);
	}
	else
	{
		avg = ((1 - wq) * avg) + (wq * segment_queue.size());
	}
	/* For debugging reasons
	printf("Queue length: %lu\n", Queue.size());
	printf("Average queue length: %f\n", avg);
	*/

	// Check if the average queue length is between minimum
	// and maximum threshold, then probabilistically drop
	// a segment
	if (minThreshold <= avg && avg < maxThreshold)
	{
		count++;
		pb = avg - minThreshold;
		pb = pb * maxp;
		pb = pb / (maxThreshold - minThreshold);
		double pa = pb / (1 - (count * pb));
		if (count == 50)
		{
			// count has reached 1/maxp,
			// Need to drop packets now
			cout << "Count has reached 1/maxp. Dropping segment" << endl;
			pa = 1.0;
		}
		double randomP = (rand() % 100) / 100.00;
		// Dropping segment with probability pa
		if (randomP <= pa)
		{
			if (count != 50)
				cout << "Dropping segment\t";
			// Resetting count to 0
			count = 0;
			result = true;
		}
		else
		{
			cout << "Buffering segment\t";
			// Initialize count to -1 since segment is buffered
			count = -1;
		}
		cout << "pa=" << pa << " randomP=" << randomP << " count=" << count << endl;
	}
	else if (maxThreshold <= avg)
	{
		// Queue size is more than max threshold allowed
		// Drop all packets
		cout << "Dropping segment cause of threshold" << endl;
		result = true;
		count = 0;
	}
	else
	{
		// Average queue length is less than minimum threshold
		// Accept all packets
		cout << "Buffering segment cause of threshold" << endl;
		// Since the average queue length is below minimum threshold, initialize count to -1
		count = -1;
	}
	// Printing the queue
	// showq(Queue);
	cout << "RED: *********END : avg=" << avg << " current=" << segment_queue.size() << " count=" << count << "**********\n\n"
			 << endl;
	return result;
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

		cout << "Segment with seq_num:ack " << segment->get_seq_num() << ":" << segment->get_acknowlegment() << " sent to " << ntohs(send_addr.sin_port) << endl;
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
	if (segment_queue.size() == QUEUE_SIZE)
	{
		cout << "Segment with seq_num:ack " << segment->get_seq_num() << ":" << segment->get_acknowlegment() << " buffer dropped" << endl;
		return;
	}
	segment_queue.push(segment);
}

bool Router::is_random_drop()
{
	auto dropped = rand() % 100 < DROP_RATE;
	return dropped;
}

int main(int argc, char *argv[])
{
	auto router_port = stoi(argv[1]);
	auto receiver_port = stoi(argv[2]);

	int buffer_size = 20;
	int drop_rate = 10;
	bool red_option = true;

	Router router(router_port, receiver_port, buffer_size, drop_rate, red_option);

	router.start();
}
