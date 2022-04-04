#include "CommandHandler/PwdHandler.hpp"

using namespace std;


vector<string> PwdHandler::handle_command(const vector<string> command_parts, User *user)
{
    if (command_parts.size() != 1)
        return {SYNTAX_ERROR, EMPTY};
    return handle_get_current_directory(user);
}

vector<string> PwdHandler::handle_get_current_directory(User *user)
{
    string current_path = user->get_current_directory();

    string bash_command = "realpath " + current_path;
    auto result = exec_command(bash_command);
    if (result.first != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    return {"257: " + result.second, EMPTY};
}