#ifndef PASSWORD_HANDLER_HPP
#define PASSWORD_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class PasswordHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
    std::vector<std::string> handle_password(std::string password, User* user);

};


#endif 