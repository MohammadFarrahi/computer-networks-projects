#include "CommandHandler/LsHandler.hpp"

using namespace std;

vector<string> LsHandler::handle_get_list_of_files(User *user)
{
  string bash_command = "ls " + user->get_current_directory() + " > file.txt";
  int status = system(bash_command.c_str());
  if (status != SUCCESS)
    return {GENERAL_ERROR, EMPTY};

  string result = read_file_to_string("file.txt");
  result.pop_back();
  status = system("rm file.txt");
  if (status != SUCCESS)
    return {GENERAL_ERROR, EMPTY};

  erase_sub_str(result, "file.txt\n");

  return {LIST_TRANSFER_DONE, result};
}
vector<string> LsHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1)
    return {SYNTAX_ERROR, EMPTY};
  return handle_get_list_of_files(user);
}
