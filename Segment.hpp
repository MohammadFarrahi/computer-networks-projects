#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>

const int ACK = 1;
const int PAYLOAD_SIZE = 1536;
const int PORT_SIZE = 4;
const int SEQ_NUM_SIZE = 4;
const int FLAG_SIZE = 2;
const int SEGMENT_SIZE = 2048;

using namespace std;

class Segment
{
private:
  int src_port;
  int dst_port;
  int flag;
  int sequence_number;
  int acknowlegment;
  char payload[PAYLOAD_SIZE];

public:
  Segment(int _src_port, int _dst_port)
  {
    this->src_port = _src_port;
    this->dst_port = _dst_port;
  }

  void set_flag(int _flag)
  {
    this->flag = _flag;
  }

  void set_payload(const char *_payload, int _sequence_number)
  {
    this->sequence_number = _sequence_number;
    strncpy(this->payload, _payload, PAYLOAD_SIZE - 1);
    this->payload[strlen(this->payload)] = '\0';
  }

  void set_acknowlegment(int ack_num)
  {
    this->acknowlegment = ack_num;
  }

  char *serialize(char *buffer)
  {
    auto dst_port_str = make_fixed_size_str(this->dst_port, PORT_SIZE);
    auto src_port_str = make_fixed_size_str(this->src_port, PORT_SIZE);
    auto ack_str = make_fixed_size_str(this->acknowlegment, SEQ_NUM_SIZE);
    auto seq_num_str = make_fixed_size_str(this->sequence_number, SEQ_NUM_SIZE);
    auto flag_str = make_fixed_size_str(this->flag, FLAG_SIZE);

    strcpy(buffer, src_port_str.c_str());
    strcpy(buffer + strlen(buffer), dst_port_str.c_str());
    strcpy(buffer + strlen(buffer), seq_num_str.c_str());
    strcpy(buffer + strlen(buffer), ack_str.c_str());
    strcpy(buffer + strlen(buffer), flag_str.c_str());

    strcpy(buffer + strlen(buffer), this->payload);
    return buffer;
  }

  string make_fixed_size_str(const int input, const int length)
  {
    ostringstream ss;

    if (input < 0)
      ss << '-';

    ss << setfill('0') << setw(length) << (input < 0 ? -input : input);

    return ss.str();
  }
};
#endif