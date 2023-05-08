#pragma once

#include <string>
#include <vector>


const int NO_NODE_EXCEPTION_CODE = 1;
const int DUPLICATE_NODE_EXCEPTION_CODE = 2;

class Util
{
public:

  static std::vector<std::string> tokenize(std::string command, std::string delim);

};