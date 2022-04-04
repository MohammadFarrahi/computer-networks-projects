#include "CommandHandler/RetrHandler.hpp"

using namespace std;


vector<string> RetrHandler::handle_command(const vector<string> command_parts, User *user)
{
        if (command_parts.size() != 2)
            return {SYNTAX_ERROR, EMPTY};
        return handle_download_file(command_parts[ARG1], user);
}

std::vector<std::string> RetrHandler::handle_download_file(string file_name, User *user)
{
    if (!is_a_file_name(file_name))
        return {SYNTAX_ERROR, EMPTY};

    if (!user_has_access_to_file(file_name, user))
        return {FILE_UNAVAILABLE, EMPTY};

    string file_path = user->get_current_directory() + file_name;
    string size_command = "stat -c%s " + file_path;
    auto file_size_info = exec_command(size_command);
    if (file_size_info.first != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    double file_size = stod(file_size_info.second);

    if (user->is_able_to_download(file_size) == false)
        return {DOWNLOAD_LIMIT_SIZE, EMPTY};

    string result = read_file_as_binary(file_path);
    user->decrease_available_size(file_size);

    string message = COLON + file_name + " downloaded.";
    Logger::get_instance()->log(user->get_username() + message);

    return {SUCCESSFUL_DOWNLOAD, result};
}