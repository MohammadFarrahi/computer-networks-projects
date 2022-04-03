#ifndef RETR_HANDLER_HPP
#define RETR_HANDLER_HPP


#include "CommandHandler/ICommand.hpp"


class RetrHandler : public ICommandHandler {
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
    std::vector<std::string> handle_download_file(std::string file_name, User* user);
};


#endif 