#include "CommandHandler/QuitHandler.hpp"

using namespace std;

vector<string> QuitHandler::handle_quit(User *user)
{
  if (user->get_state() != User::State::LOGGED_IN)
    return {GENERAL_ERROR, EMPTY};

  user->set_state(User::State::WAITING_FOR_USERNAME);

  Logger::get_instance()->log(user->get_username() + COLON + "logged out.");

  return {SUCCESSFUL_QUIT, EMPTY};
}

vector<string> QuitHandler::handle_command(const vector<string> command_parts, User *user)
{
  if (command_parts.size() != 1)
    return {SYNTAX_ERROR, EMPTY};
  return handle_quit(user);
}
