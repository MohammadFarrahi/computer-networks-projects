#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>

const int ACK = 1;
const int FILE_NAME = 2;
const int PAYLOAD_SIZE = 1536;
const int PORT_SIZE = 5;
const int SEQ_NUM_SIZE = 4;
const int FLAG_SIZE = 2;
const int SEGMENT_SIZE = 2048;

const int WINDOW_SIZE = 10;
const int MAX_SEQ = (2 * WINDOW_SIZE) + 1;

using namespace std;

class Segment
{
private:
  int src_port;
  int dst_port;
  int flag;
  int sequence_number;
  int acknowlegment;
  time_t sent_time;
  char payload[PAYLOAD_SIZE+1];

public:
  Segment();
  Segment(const char *_payload);
  // Segment(char *buffer);

  void set_flag(int _flag);
  void set_seq_num(int _sequence_number);
  void set_ports(int _src_port, int _dst_port);
  void set_acknowlegment(int ack_num);
  void set_sent_time(time_t time);

  time_t get_sent_time();
  int get_seq_num();
  int get_acknowlegment();
  char *get_payload();
  int get_src_port();
  int get_dst_port();
  int get_flag();

  char *serialize(char *buffer);
  void deserialize(char *buffer);

  string slice(char *buffer, int start, int size);
  string make_fixed_size_str(const int input, const int length);
};
#endif