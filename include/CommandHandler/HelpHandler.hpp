#ifndef HELP_HANDLER_HPP
#define HELP_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class HelpHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_help();
};

#endif