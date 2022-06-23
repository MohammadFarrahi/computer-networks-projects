#include "ClientReceiver.hpp"

#include <fstream>
#include <iostream>

ClientReceiver::ClientReceiver(int sender_port, int receiver_port)
{
  this->expected_seq_num = 0;
  this->sender_port = sender_port;
  this->receiver_port = receiver_port;
}

bool ClientReceiver::process_packet(char *input_buffer, char *output_buffer)
{
  auto segment = new Segment();
  segment->deserialize(input_buffer);

  bool success = false;

  if (segment->get_seq_num() == this->expected_seq_num)
  {
    make_ack(segment, output_buffer);
    if (filename == "")
      set_file_name(segment);
    else
      append_to_file(segment);
    
    this->expected_seq_num++;
    success = true;
  }

  delete segment;
  return success;
}

void ClientReceiver::set_file_name(Segment *segment)
{
  cout << "Name of file : " << segment->get_payload() << endl;
  this->filename = segment->get_payload();
}

void ClientReceiver::append_to_file(Segment *segment)
{
  ofstream file(this->filename, ios::binary | ios::app);
  file.write(segment->get_payload(), strlen(segment->get_payload()));
  file.close();
}

void ClientReceiver::make_ack(Segment *segment, char *buffer)
{
  Segment ack_seg;
  ack_seg.set_flag(ACK);
  ack_seg.set_acknowlegment(expected_seq_num);
  ack_seg.set_ports(this->receiver_port, segment->get_src_port());

  ack_seg.serialize(buffer);
}