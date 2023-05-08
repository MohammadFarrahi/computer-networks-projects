#ifndef DELE_HANDLER_HPP
#define DELE_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

class DeleHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_delete_directory(std::string dir_path, User *user);
  std::vector<std::string> handle_delete_file(std::string file_name, User *user);
};

#endif