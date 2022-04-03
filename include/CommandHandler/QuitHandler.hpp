#ifndef QUIT_HANDLER_HPP
#define QUIT_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class QuitHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_logout(User *user);
};

#endif