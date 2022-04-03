#ifndef HELP_HANDLER_HPP
#define HELP_HANDLER_HPP

#include "CommandHandler/ICommand.hpp"

#define USER_DESCRIPTION "USER [name], Its argument is used to specify the user's string. It is used for user authentication.\n"
#define PASS_DESCRIPTION "PASS [password], Its argument is used to specify the user's password. It is used for user authentication.\n"
#define PWD_DESCRIPTION "PWD, It is used to print the name of the current working directory.\n"
#define MKD_DESCRIPTION "MKD [path], Its argument is used to specify the directory's path. It is usede to create a new directory.\n"
#define DELE_DESCRIPTION "DELE [flag] [path], Its argument is used to specify the file/directory's path. It flag is used to specify whether a file (-f) or a directory (-d) will be removed. It is usede to remove a file or directory.\n"
#define LS_DESCRIPTION "LS. It is used to print the list of files/directories in the current working directory.\n"
#define CWD_DESCRIPTION "CWD [path], Its argument is used to specify the directory's path. It is used to change the current working directory.\n"
#define RENAME_DESCRIPTION "RENAME [from] [to], Its arguments are used to specify the old and new file's name. It is used to change A file's name.\n"
#define RETR_DESCRIPTION "RETR [name], Its argument is used to specify the file's name. It is used to download a file.\n"
#define HELP_DESCRIPTION "HELP, It is used to display information about builtin commands.\n"
#define QUIT_DESCRIPTION "QUIT, It is used to sign out from the server.\n"

class HelpHandler : public ICommandHandler
{
public:
  std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user);

private:
  std::vector<std::string> handle_help();
};

#endif