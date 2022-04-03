#ifndef USERNAME_HANDLER_HPP
#define USERNAME_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class LoginRequiredHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);
  LoginRequiredHandler(ICommandHandler *inner_handler);

private:
  ICommandHandler *inner_handler;
};

#endif