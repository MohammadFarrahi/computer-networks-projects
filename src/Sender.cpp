#include "Sender.hpp"

#include <iostream>


Sender::Sender(int sender_port, int receiver_port)
{
  this->sender_port = sender_port;
  this->receiver_port = receiver_port;
}

void Sender::start(string file_location)
{
  setup_socket();

  auto segments = slice_file(file_location);
  vector<bool> segments_ack(segments.size(), false);

  int window_start = 0;

  // send first window
  send_bulk(segments, window_start);

  while (true)
  {
    if (has_segment_expired(segments[window_start]))
    {
      send_bulk(segments, window_start);
    }
    else
    {
      auto ack_segment = receive_ack();
      if (ack_segment == NULL)
        continue;

      if (ack_segment->get_acknowlegment() == segments[window_start].get_seq_num())
      {
        segments_ack[window_start] = true;
        auto updated_window_start = update_window_start(segments_ack, window_start);
        send_bulk(segments, updated_window_start, updated_window_start-window_start);
        window_start = updated_window_start;
      }
      else
      {
        segments_ack[get_index(window_start, ack_segment->get_acknowlegment())] = true;
      }
      delete ack_segment;
    }
  }
}

int Sender::update_window_start(vector<bool>& segments_ack, int window_start)
{ 
  while(segments_ack[window_start])
    window_start++;
  
  return window_start;
}

void Sender::setup_socket()
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
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(this->receiver_port);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Filling client information
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(this->sender_port);
	cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Bind the socket with the client address
	// if (bind(sockfd, (const struct sockaddr *)&cliaddr,
	// 				 sizeof(cliaddr)) < 0)
	// {
	// 	cerr << "bind failed" << endl;
	// 	exit(EXIT_FAILURE);
	// }
}

vector<Segment> Sender::slice_file(string file_location)
{
  vector<Segment> result;
  char buffer[PAYLOAD_SIZE];

  result.push_back(Segment(file_location.c_str()));


  std::ifstream infile(file_location);
  while (infile.read(buffer, PAYLOAD_SIZE))
  {
    result.push_back(Segment(buffer));
    memset(buffer, 0, strlen(buffer));
  }
  result.push_back(Segment(buffer));

  return result;
}

void Sender::send_bulk(vector<Segment> &segments, int start_from, int count)
{
  for (int i = 0; i < count; i++)
  {
    send_segment(segments[i + start_from], i + start_from);
  }
}

void Sender::send_segment(Segment &segment, int segment_index)
{
  segment.set_ports(this->sender_port, this->receiver_port);
  segment.set_seq_num(get_seq_num(segment_index));
  // send with socket
  char buffer[SEGMENT_SIZE];
  segment.serialize(buffer);

  // age bug dasht moshkele ine
  sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));

  
  segment.set_sent_time(time(NULL));
}

int Sender::get_seq_num(int segment_index)
{
  return segment_index % (WINDOW_SIZE + 1);
}

int Sender::get_index(int start_window, int seq_num)
{
  int window_start_seq_num = get_seq_num(start_window);
  int delta = seq_num - window_start_seq_num;
  if(delta < 0)
    delta = WINDOW_SIZE + delta;
  return start_window + delta;
}

bool Sender::has_segment_expired(Segment segment)
{
  auto seg_time = segment.get_sent_time();
  return time(NULL) - seg_time > TIME_OUT_LENGTH;
}

Segment *Sender::receive_ack()
{

  char buffer[SEGMENT_SIZE];
  fd_set read_fds;
  int nbytes;
  socklen_t servaddr_len = sizeof(servaddr);

  FD_ZERO(&read_fds);
  FD_SET(sockfd, &read_fds);
  int n = select(sockfd + 1, &read_fds, 0, 0, 0);
  if (n < 0)
  {
    cerr << "ERROR Server : select()\n"
         << endl;
    close(sockfd);
    exit(1);
  }

  if (FD_ISSET(sockfd, &read_fds))
  {
    nbytes = recvfrom(sockfd, buffer, SEGMENT_SIZE, 0, (struct sockaddr *)&servaddr, &servaddr_len);
    if (nbytes < 0)
    {
      cerr << "ERROR in recvfrom()" << endl;
      close(sockfd);
      exit(1);
    }

    auto return_segment = new Segment();
    return_segment->deserialize(buffer);
    return return_segment;
  }
  FD_CLR(sockfd, &read_fds);
  return nullptr;
}


int main(int argc, char *argv[])
{
	auto sender_port = stoi(argv[1]);
	auto receiver_port = stoi(argv[2]);
	Sender sender(sender_port, receiver_port);

	sender.start("./README.md");
}