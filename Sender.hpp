#ifndef SENDER_HPP
#define SENDER_HPP

#include <string>
#include <vector>
#include <fstream>

#include "Segment.hpp"

using namespace std;

class Sender
{
public:
  void start(int sender_port, int receiver_port, string file_location)
  {
  }

  vector<Segment> slice_file(string file_location)
  {
    vector<Segment> result;
    char buffer[PAYLOAD_SIZE];

    std::ifstream infile(file_location);

    while (infile.read(buffer, PAYLOAD_SIZE))
    {
      result.push_back(Segment(buffer));
      memset(buffer, 0, strlen(buffer));
    }
    result.push_back(Segment(buffer));

    return result;
  }

private:
};

#endif