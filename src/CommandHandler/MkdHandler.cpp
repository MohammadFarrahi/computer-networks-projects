#include "CommandHandler/MkdHandler.hpp"

using namespace std;

vector<string> MkdHandler::handle_mkd(string dir_path, User *user)
{
  string bash_command = "mkdir " + user->get_current_directory() + dir_path;
  int status = system(bash_command.c_str());
  if (status == SUCCESS)
  {
    string message = COLON + dir_path + " created.";
    Logger::get_instance()->log(user->get_username() + message);
    return {CREATE_CODE + message, EMPTY};
  }
  return {GENERAL_ERROR, EMPTY};
}

vector<string> MkdHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 2)
    return {SYNTAX_ERROR, EMPTY};
  return handle_mkd(command_parts[ARG1], user);
}
