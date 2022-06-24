#ifndef CLIENT_RECEIVER_HPP
#define CLIENT_RECEIVER_HPP

#include "Segment.hpp"

class ClientReceiver
{
public:
  ClientReceiver(int sender_port, int receiver_port);
  bool process_packet(Segment* segment, char *output_buffer);

private:
  int expected_seq_num;
  int sender_port;
  int receiver_port;
  string filename;
  int last_ack_sent;

  void make_ack(Segment *segment, char *buffer);
  void append_to_file(Segment *segment);
  void set_file_name(Segment* segment);
  void increment_expected_seq();
};

#endif