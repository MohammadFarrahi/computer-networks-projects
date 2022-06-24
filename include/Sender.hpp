#ifndef SENDER_HPP
#define SENDER_HPP

#include <string>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Segment.hpp"

using namespace std;

const int TIME_OUT_LENGTH = 4;


class Sender
{
public:
  Sender(int sender_port, int receiver_port, int router_port);
  void start(string file_location);


private:
  int sender_port;
  int receiver_port;
  int router_port;

  struct sockaddr_in router_addr;
  int sockfd;

  void setup_socket();
  Segment* receive_ack();

  void send_bulk(vector<Segment> &segments, int start_from, int count = WINDOW_SIZE);
  void send_segment(Segment& segment, int segment_index);
  int get_seq_num(int segment_index);
  int get_index(int start_window, int seq_num);
  bool has_segment_expired(Segment segment);
  int update_window_start(vector<bool>& segments_ack, int window_start);
  vector<Segment> slice_file(string file_location);
};

#endif