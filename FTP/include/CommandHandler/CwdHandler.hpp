#ifndef CWD_HANDLER_HPP
#define CWD_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class CwdHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_cwd(std::string dir_path, User* user);
};


#endif 