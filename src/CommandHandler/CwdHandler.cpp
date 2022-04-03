#include "CommandHandler/CwdHandler.hpp"

using namespace std;

vector<string> CwdHandler::handle_change_working_directory(string dir_path, User *user)
{
  string check_validity_command = "realpath " + dir_path + " > file.txt";
  int status1 = system(check_validity_command.c_str());
  int status2 = system("rm file.txt");
  if (status1 != SUCCESS || status2 != SUCCESS)
    return {GENERAL_ERROR, EMPTY};

  if (dir_path == ROOT)
    user->set_current_directory(ROOT);
  else
    user->set_current_directory(user->get_current_directory() + dir_path + "/");

  return {SUCCESSFUL_CHANGE, EMPTY};
}

vector<string> CwdHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1 && command_parts.size() != 2)
    return {SYNTAX_ERROR, EMPTY};
  return handle_change_working_directory(((command_parts.size() >= 2) ? command_parts[ARG1] : ROOT), user);
}
