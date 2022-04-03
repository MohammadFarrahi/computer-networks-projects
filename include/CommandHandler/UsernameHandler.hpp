#ifndef USERNAME_HANDLER_HPP
#define USERNAME_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class UsernameHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_username(std::string username, User* user);

};


#endif 