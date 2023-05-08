#ifndef LS_HANDLER_HPP
#define LS_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class LsHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_ls(User *user);
};

#endif