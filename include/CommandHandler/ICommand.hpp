#ifndef I_COMMAND_HANDLER_HPP
#define I_COMMAND_HANDLER_HPP

#include <vector>
#include <string>
#include "User.hpp"

#include "UserManager.hpp"


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

class ICommandHandler
{
public:
  virtual std::vector<std::string> handle_command(const std::vector<std::string> command_parts, User *user) = 0;

protected:
  bool is_a_file_name(std::string file_name);
  bool user_has_access_to_file(std::string file_name, User* user);

};

#endif