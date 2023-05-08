#ifndef PWD_HANDLER_HPP
#define PWD_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class PwdHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
    std::vector<std::string> handle_pwd(User* user);
};


#endif 