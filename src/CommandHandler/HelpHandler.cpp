#include "CommandHandler/HelpHandler.hpp"

using namespace std;

std::vector<std::string> HelpHandler::handle_help()
{
  string info = "214\n";
  info += USER_DESCRIPTION;
  info += PASS_DESCRIPTION;
  info += PWD_DESCRIPTION;
  info += MKD_DESCRIPTION;
  info += DELE_DESCRIPTION;
  info += LS_DESCRIPTION;
  info += CWD_DESCRIPTION;
  info += RENAME_DESCRIPTION;
  info += RETR_DESCRIPTION;
  info += HELP_DESCRIPTION;
  info += QUIT_DESCRIPTION;
  return {info, EMPTY};
}

vector<string> HelpHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1)
    return {SYNTAX_ERROR, EMPTY};
  return handle_help();
}
