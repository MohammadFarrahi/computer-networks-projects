#include "CommandHandler/HelpHandler.hpp"
#include <sstream>

using namespace std;

std::vector<std::string> HelpHandler::handle_help()
{
  CommandDescription descriptor;
  stringstream ss;
  ss << "214:" << endl;
  ss << descriptor.USER << endl;
  ss << descriptor.PASS << endl;
  ss << descriptor.PWD << endl;
  ss << descriptor.MKD << endl;
  ss << descriptor.DELE << endl;
  ss << descriptor.LS << endl;
  ss << descriptor.CWD << endl;
  ss << descriptor.RENAME << endl;
  ss << descriptor.RETR << endl;
  ss << descriptor.HELP << endl;
  ss << descriptor.QUIT << endl;
  return {ss.str(), EMPTY};
}

vector<string> HelpHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1)
    return {SYNTAX_ERROR, EMPTY};
  return handle_help();
}
