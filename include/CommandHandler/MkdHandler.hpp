#ifndef MKD_HANDLER_HPP
#define MKD_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class MkdHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_create_new_directory(std::string dir_path, User *user);
};

#endif