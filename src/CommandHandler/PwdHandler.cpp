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
    if (current_path == ROOT)
        current_path = ".";

    string bash_command = "realpath " + current_path + " > file.txt";
    int status = system(bash_command.c_str());
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    string result = read_file_to_string("file.txt");
    result.pop_back();
    status = system("rm file.txt");
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    return {"257: " + result, EMPTY};
}