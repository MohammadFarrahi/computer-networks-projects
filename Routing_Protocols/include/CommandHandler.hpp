#pragma once

#include "Network.hpp"

#include <string>


class CommandHandler
{
public:
  CommandHandler() : network() {};
  void start();


private:
  Network network;

  void run_command(std::string command);

};