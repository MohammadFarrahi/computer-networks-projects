#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "Utilities.hpp"
#include "User.hpp"
#include "UserInfo.hpp"
#include "Logger.hpp"

#include "ServerConfig.hpp"
#include "UserConfig.hpp"
#include "UserManager.hpp"
#include "CommandHandler/ICommand.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sys/stat.h>

#define COMMAND 0
#define ARG1 1
#define ARG2 2
#define SUCCESS 0
#define EMPTY " "
#define COLON ": "
#define ROOT ""
#define BACK_SLASH "/"
#define USER_COMMAND "user"
#define PASS_COMMAND "pass"
#define PWD_COMMAND "pwd"
#define MKD_COMMAND "mkd"
#define DELE_COMMAND "dele"
#define LS_COMMAND "ls"
#define CWD_COMMAND "cwd"
#define RENAME_COMMAND "rename"
#define RETR_COMMAND "retr"
#define HELP_COMMAND "help"
#define QUIT_COMMAND "quit"

class CommandHandler {
public:
    CommandHandler(UserConfig user_config);

    ~CommandHandler();
    std::vector<std::string> do_command(int user_socket, char* command);

private:
    std::map<std::string, ICommandHandler*> command_handler_collection;
};

#endif
