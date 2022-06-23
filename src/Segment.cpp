#include "Segment.hpp"
#include <iostream>

Segment::Segment(const char *_payload)
{
  this->acknowlegment = 0;
  this->sequence_number = 0;
  this->flag = 0;
  strncpy(this->payload, _payload, PAYLOAD_SIZE);
  cout << "in segment construct" << endl;
  cout << strlen(this->payload) << endl << endl << endl;
  this->payload[PAYLOAD_SIZE] = '\0';
  // this->payload[strlen(this->payload)+1] = '5';
  cout << strlen(this->payload) << endl << endl << endl;

}

Segment::Segment()
{
  this->payload[0] = '\0';
  this->acknowlegment = 0;
  this->sequence_number = 0;
  this->flag = 0;
}

void Segment::set_flag(int _flag)
{
  this->flag = _flag;
}

void Segment::set_seq_num(int _sequence_number)
{
  this->sequence_number = _sequence_number;
}

void Segment::set_ports(int _src_port, int _dst_port)
{
  this->src_port = _src_port;
  this->dst_port = _dst_port;
}

void Segment::set_acknowlegment(int ack_num)
{
  this->acknowlegment = ack_num;
}

void Segment::set_sent_time(time_t time)
{
  this->sent_time = time;
}

time_t Segment::get_sent_time()
{
  return this->sent_time;
}

int Segment::get_seq_num()
{
  return this->sequence_number;
}

int Segment::get_acknowlegment()
{
  return this->acknowlegment;
}

char* Segment::get_payload()
{
  return this->payload;
}

int Segment::get_dst_port()
{
  return this->dst_port;
}

int Segment::get_src_port()
{
  return this->src_port;
}


char *Segment::serialize(char *buffer)
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
  buffer[strlen(buffer)] = '\0';
  cout << "\n\nbuffer size: " << strlen(buffer) << "\n" << endl;
  return buffer;
}

void Segment::deserialize(char *buffer)
{
  int index = 0;
  this->src_port = stoi(slice(buffer, index, PORT_SIZE));
  index += PORT_SIZE;

  this->dst_port = stoi(slice(buffer, index, PORT_SIZE));
  index += PORT_SIZE;

  this->sequence_number = stoi(slice(buffer, index, SEQ_NUM_SIZE));
  index += SEQ_NUM_SIZE;

  this->acknowlegment = stoi(slice(buffer, index, SEQ_NUM_SIZE));
  index += SEQ_NUM_SIZE;

  this->flag = stoi(slice(buffer, index, FLAG_SIZE));
  index += FLAG_SIZE;

  strncpy(this->payload, buffer + index, strlen(buffer) - index);

  this->payload[strlen(buffer) - index] = '\0';

// cout << "IN deserialize" << endl;
// cout << "src port: " << this->src_port << endl;
// cout << "dsr port: " << this->dst_port << endl;
// cout << "seq: " << this->sequence_number << endl;
// cout << "ack: " << this->acknowlegment << endl;
// cout << "flag: " << this->flag << endl;


}

string Segment::slice(char *buffer, int start, int size)
{
  return string(buffer).substr(start, size);
}

string Segment::make_fixed_size_str(const int input, const int length)
{
  ostringstream ss;

  if (input < 0)
    ss << '-';

  ss << setfill('0') << setw(length) << (input < 0 ? -input : input);

  return ss.str();
}