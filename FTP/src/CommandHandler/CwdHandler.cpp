#include "CommandHandler/CwdHandler.hpp"

using namespace std;

vector<string> CwdHandler::handle_cwd(string dir_path, User *user)
{
  auto full_path = exec_command("realpath " + user->get_current_directory() + dir_path);
  if (full_path.first != SUCCESS || exec_command("test -d " + full_path.second).first != SUCCESS)
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
  return handle_cwd(((command_parts.size() >= 2) ? command_parts[ARG1] : ""), user);
}
