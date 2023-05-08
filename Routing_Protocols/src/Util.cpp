#include "Util.hpp"

#include <sstream>
#include <iostream>

using namespace std;

vector<string> Util::tokenize(string command, string delim)
{
  vector<string> result;
  size_t pos = 0;
  std::string token;
  while ((pos = command.find(delim)) != std::string::npos)
  {
    token = command.substr(0, pos);
    result.push_back(token);
    command.erase(0, pos + delim.length());
  }
  result.push_back(command);
  return result;
}