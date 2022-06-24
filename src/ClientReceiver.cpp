#include "ClientReceiver.hpp"

#include <fstream>
#include <iostream>

ClientReceiver::ClientReceiver(int sender_port, int receiver_port)
{
  this->expected_seq_num = 0;
  this->last_ack_sent = -1;
  
  this->sender_port = sender_port;
  this->receiver_port = receiver_port;
}

bool ClientReceiver::process_packet(Segment *segment, char *output_buffer)
{
  bool success = false;

  if (segment->get_seq_num() < this->expected_seq_num)
  {
    make_ack(segment, output_buffer);
  }
  else if (segment->get_seq_num() == this->expected_seq_num)
  {
    cout << "Segment with seq_num " << segment->get_seq_num() << " received" << endl;
    make_ack(segment, output_buffer);

    if (segment->get_flag() == FILE_NAME)
      set_file_name(segment);
    else
      append_to_file(segment);

    increment_expected_seq();
    success = true;
  }

  delete segment;
  return success;
}

void ClientReceiver::set_file_name(Segment *segment)
{
  cout << "Name of file : " << segment->get_payload() << endl;
  this->filename = segment->get_payload();
  ofstream file(this->filename, ios::ate);
  file.close();
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
  ack_seg.set_acknowlegment(segment->get_seq_num());
  ack_seg.set_ports(this->receiver_port, segment->get_src_port());

  ack_seg.serialize(buffer);
  cout << "ack segment for segment " << segment->get_seq_num() << " sent" << endl;
}

void ClientReceiver::increment_expected_seq()
{
  this->last_ack_sent++;
  this->expected_seq_num = ++this->expected_seq_num % (WINDOW_SIZE + 1);
}
