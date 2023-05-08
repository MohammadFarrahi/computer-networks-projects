#include "CommandHandler/DeleHandler.hpp"

using namespace std;

vector<string> DeleHandler::handle_delete_directory(string dir_path, User *user)
{
  string bash_command = "rm -r " + user->get_current_directory() + dir_path;
  int status = system(bash_command.c_str());
  if (status == SUCCESS)
  {
    string message = COLON + dir_path + " deleted.";
    Logger::get_instance()->log(user->get_username() + message);
    return {DELETE_CODE + message, EMPTY};
  }
  return {GENERAL_ERROR, EMPTY};
}

vector<string> DeleHandler::handle_delete_file(string file_name, User *user)
{
  if (!is_a_file_name(file_name))
    return {SYNTAX_ERROR, EMPTY};

  if (!user_has_access_to_file(file_name, user))
    return {FILE_UNAVAILABLE, EMPTY};

  string bash_command = "rm " + user->get_current_directory() + file_name;
  int status = system(bash_command.c_str());
  if (status == SUCCESS)
  {
    string message = COLON + file_name + " deleted.";
    Logger::get_instance()->log(user->get_username() + message);
    return {DELETE_CODE + message, EMPTY};
  }
  return {GENERAL_ERROR, EMPTY};
}

vector<string> DeleHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 3)
    return {SYNTAX_ERROR, EMPTY};

  if (command_parts[ARG1] == DELE_DIRECTORY_OPTION)
    return handle_delete_directory(command_parts[ARG2], user);

  else if (command_parts[ARG1] == DELE_FILE_OPTION)
    return handle_delete_file(command_parts[ARG2], user);

  else
    return {SYNTAX_ERROR, EMPTY};
}
