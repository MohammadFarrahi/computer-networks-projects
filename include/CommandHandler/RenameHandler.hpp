#ifndef RN_HANDLER_HPP
#define RN_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class RenameHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
    std::vector<std::string> handle_rename_file(std::string old_name, std::string new_name, User* user);
};


#endif 