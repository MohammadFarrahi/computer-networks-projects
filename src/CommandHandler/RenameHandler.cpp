#include "CommandHandler/RenameHandler.hpp"

using namespace std;


vector<string> RenameHandler::handle_command(const vector<string> command_parts, User *user)
{
    if (command_parts.size() != 3)
        return {SYNTAX_ERROR, EMPTY};
    return handle_rename_file(command_parts[ARG1], command_parts[ARG2], user);
}

std::vector<std::string> RenameHandler::handle_rename_file(string old_name, string new_name, User *user)
{
    if (!is_a_file_name(old_name) || !is_a_file_name(new_name))
        return {SYNTAX_ERROR, EMPTY};

    if (!user_has_access_to_file(old_name, user))
        return {FILE_UNAVAILABLE, EMPTY};

    string bash_command = "mv " + user->get_current_directory() + old_name + " " +
                          user->get_current_directory() + new_name;
    int status = system(bash_command.c_str());
    if (status == SUCCESS)
        return {SUCCESSFUL_CHANGE, EMPTY};
    return {GENERAL_ERROR, EMPTY};
}