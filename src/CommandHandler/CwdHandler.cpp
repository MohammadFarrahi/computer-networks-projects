#include "CommandHandler/CwdHandler.hpp"

using namespace std;

vector<string> CwdHandler::handle_change_working_directory(string dir_path, User *user)
{
  
  // dir_path = exec_command("realpath " + dir_path).second + SLASH;
  auto full_path = exec_command("realpath " + dir_path);
  if (full_path.first != SUCCESS)
    return {GENERAL_ERROR, EMPTY};
  
  dir_path = full_path.second + SLASH;
  if(dir_path.rfind(Constant::ROOT, 0) != 0)
    return {GENERAL_ERROR, EMPTY};
  
  user->set_current_directory(dir_path);
  return {SUCCESSFUL_CHANGE, EMPTY};
}

vector<string> CwdHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1 && command_parts.size() != 2)
    return {SYNTAX_ERROR, EMPTY};
  return handle_change_working_directory(((command_parts.size() >= 2) ? command_parts[ARG1] : Constant::ROOT), user);
}
