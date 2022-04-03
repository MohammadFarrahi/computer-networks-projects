#ifndef CWD_HANDLER_HPP
#define CWD_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class CwdHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_change_working_directory(std::string dir_path, User* user);
};


#endif 