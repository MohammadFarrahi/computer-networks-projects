#include "LoginRequiredHandler.hpp"

LoginRequiredHandler::LoginRequiredHandler(ICommandHandler *inner_handler)
{
  this->inner_handler = inner_handler;
}

std::vector<std::string> LoginRequiredHandler::handle_command(const std::vector<std::string> command_parts, User *user)
{
  if (user->get_state() != User::State::LOGGED_IN)
    return {NOT_AUTHORIZED, EMPTY};
  else
  {
    return inner_handler->handle_command(command_parts, user);
  }
}
