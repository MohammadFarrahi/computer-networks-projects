#include "CommandHandler/RetrHandler.hpp"

using namespace std;


vector<string> RetrHandler::handle_command(const vector<string> command_parts, User *user)
{
        if (command_parts.size() != 2)
            return {SYNTAX_ERROR, EMPTY};
        return handle_retr(command_parts[ARG1], user);
}

std::vector<std::string> RetrHandler::handle_retr(string file_name, User *user)
{
    if (!is_a_file_name(file_name))
        return {SYNTAX_ERROR, EMPTY};

    if (!user_has_access_to_file(file_name, user))
        return {FILE_UNAVAILABLE, EMPTY};

    string file_path = user->get_current_directory() + file_name;

    double file_size = get_file_size(user->get_current_directory() + file_name);
    if (file_size < 0)
        return {GENERAL_ERROR, EMPTY};

    if (user->is_able_to_download(file_size) == false)
        return {DOWNLOAD_LIMIT_SIZE, EMPTY};

    string result = read_file_as_binary(file_path);
    user->decrease_available_size(file_size);

    string message = COLON + file_name + " downloaded.";
    Logger::get_instance()->log(user->get_username() + message);

    return {SUCCESSFUL_DOWNLOAD, result};
}