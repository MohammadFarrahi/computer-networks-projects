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

#define DELETE_CODE "250"
#define CREATE_CODE "257"

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

#define DELE_DIRECTORY_OPTION "-d"
#define DELE_FILE_OPTION "-f"

#define USERNAME_ACCEPTED "331: User name Okay, need password."
#define BAD_SEQUENCE "503: Bad sequence of commands."
#define SUCCESSFUL_LOGIN "230: User looged in, proceed. Logged out if appropriate."
#define INVALID_USER_PASS "430: Invalid username or password"
#define FILE_UNAVAILABLE "550: File unavailable."
#define LIST_TRANSFER_DONE "226: List transfer done."
#define SUCCESSFUL_CHANGE "250: Successful change."
#define SUCCESSFUL_DOWNLOAD "226: Successful Download."
#define SUCCESSFUL_QUIT "221: Successful Quit."
#define NOT_AUTHORIZED "332: Need account for login."
#define SYNTAX_ERROR "501: Syntax error in parameters or arguments."
#define GENERAL_ERROR "500: Error"
#define DOWNLOAD_LIMIT_SIZE "‫‪425:‬‬ ‫‪Can't‬‬ ‫‪open‬‬ ‫‪data‬‬ ‫‪connection.‬‬"

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

class CommandHandler {
public:
    CommandHandler(UserConfig user_config);

    ~CommandHandler();

    // UserManager* get_user_manager();

    std::vector<std::string> do_command(int user_socket, char* command);

    std::vector<std::string> handle_username(std::string username, User* user);
    std::vector<std::string> handle_password(std::string password, User* user);
    std::vector<std::string> handle_get_current_directory(User* user);
    std::vector<std::string> handle_create_new_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_delete_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_delete_file(std::string file_name, User* user);
    std::vector<std::string> handle_get_list_of_files(User* user);
    std::vector<std::string> handle_change_working_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_rename_file(std::string old_name, std::string new_name, User* user);
    std::vector<std::string> handle_download_file(std::string file_name, User* user);
    std::vector<std::string> handle_help();
    std::vector<std::string> handle_logout(User* user);

    bool is_a_file_name(std::string file_name);
    bool user_has_access_to_file(std::string file_name, User* user);

private:
    // UserManager* user_manager;
    std::map<std::string, ICommandHandler*> command_handler_collection;
};

#endif
