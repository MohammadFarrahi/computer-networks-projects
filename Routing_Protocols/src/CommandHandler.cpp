#include "CommandHandler.hpp"
#include "Util.hpp"

#include <iostream>

using namespace std;

void CommandHandler::start()
{
  string command;

  while (getline(cin, command, '\n'))
  {
    try
    {
      run_command(command);
    }
    catch(int e)
    {
      if(e == NO_NODE_EXCEPTION_CODE)
        cout << "No Node with that index" << endl;
      else if(e == DUPLICATE_NODE_EXCEPTION_CODE)
        cout << "Duplicate Node with that index" << endl;
    }
    
  }
}

void CommandHandler::run_command(string command_line)
{
  auto command_parts = Util::tokenize(command_line, " ");

  string command = command_parts[0];
  command_parts.erase(command_parts.begin());

  if (command == "topology")
  {
    this->network.create_topology(command_parts);
  }
  else if (command == "show")
  {
    this->network.show_network();
  }
  else if (command == "modify")
  {
    this->network.modify(command_parts);
  }
  else if (command == "remove")
  {
    this->network.remove(command_parts);
  }
  else if (command == "lsrp")
  {
    this->network.lsrp_algo(command_parts);
  }
  else if (command == "dvrp")
  {
    this->network.dvrp_algo(command_parts);
  }
}