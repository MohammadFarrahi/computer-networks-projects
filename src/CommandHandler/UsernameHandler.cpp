#include "CommandHandler/UsernameHandler.hpp"

using namespace std;

// vector<std::string> UsernameHandler::handle_username(string username, User *user)
// {
//   if (user->get_state() != User::State::WAITING_FOR_USERNAME)
//     return {BAD_SEQUENCE, EMPTY};

//   UserInfo *user_info = user_manager->get_user_info_by_username(username);

//   if (user_info == nullptr)
//     return {INVALID_USER_PASS, EMPTY};

//   user->set_state(User::State::WAITING_FOR_PASSWORD);
//   user->set_user_info(user_info);
//   user->set_current_directory(ROOT);

//   return {USERNAME_ACCEPTED, EMPTY};
// }

vector<string> UsernameHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 2)
    return {SYNTAX_ERROR, EMPTY};
  return handle_username(command_parts[ARG1], user);
}
