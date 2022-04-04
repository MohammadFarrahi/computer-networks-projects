#include "CommandHandler/LsHandler.hpp"

using namespace std;

vector<string> LsHandler::handle_get_list_of_files(User *user)
{
  string bash_command = "ls " + user->get_current_directory();
  auto result = exec_command(bash_command);
  if (result.first != SUCCESS)
    return {GENERAL_ERROR, EMPTY};

  return {LIST_TRANSFER_DONE, result.second};
}
vector<string> LsHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1)
    return {SYNTAX_ERROR, EMPTY};
  return handle_get_list_of_files(user);
}
