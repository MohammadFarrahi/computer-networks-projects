#include "CommandHandler.hpp"
#include "CommandHandler/CwdHandler.hpp"
#include "CommandHandler/UsernameHandler.hpp"
#include "CommandHandler/PasswordHandler.hpp"
#include "CommandHandler/PwdHandler.hpp"
#include "CommandHandler/RenameHandler.hpp"
#include "CommandHandler/RetrHandler.hpp"
#include "CommandHandler/LoginRequiredHandler.hpp"

#include "UserManager.hpp"

using namespace std;

CommandHandler::CommandHandler(UserConfig user_config)
{
    command_handler_collection[USER_COMMAND] = new UsernameHandler();
    command_handler_collection[PASS_COMMAND] = new PasswordHandler();
    command_handler_collection[PWD_COMMAND] = new LoginRequiredHandler(new PwdHandler());
    command_handler_collection[CWD_COMMAND] = new LoginRequiredHandler(new CwdHandler());
    command_handler_collection[RENAME_COMMAND] = new LoginRequiredHandler(new RenameHandler());
    command_handler_collection[RETR_COMMAND] = new LoginRequiredHandler(new RetrHandler());
}

CommandHandler::~CommandHandler()
{
}

vector<string> CommandHandler::do_command(int user_socket, char *command)
{
    vector<string> command_parts = parse_command(command);

    User *user = UserManager::get_instance()->get_user_by_socket(user_socket);

    if (user == nullptr)
        return {GENERAL_ERROR, EMPTY};

    if (command_parts[COMMAND] == USER_COMMAND)
    {
        return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);
    }

    else if (command_parts[COMMAND] == PASS_COMMAND)
    {
        return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);
    }

    else if (command_parts[COMMAND] == PWD_COMMAND)
    {
        return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);
    }

    else if (command_parts[COMMAND] == MKD_COMMAND)
    {
        if (command_parts.size() != 2)
            return {SYNTAX_ERROR, EMPTY};
        return handle_create_new_directory(command_parts[ARG1], user);
    }

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_DIRECTORY_OPTION)
    {
        if (command_parts.size() != 3)
            return {SYNTAX_ERROR, EMPTY};
        return handle_delete_directory(command_parts[ARG2], user);
    }

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_FILE_OPTION)
    {
        if (command_parts.size() != 3)
            return {SYNTAX_ERROR, EMPTY};
        return handle_delete_directory(command_parts[ARG2], user);
    }

    else if (command_parts[COMMAND] == LS_COMMAND)
    {
        if (command_parts.size() != 1)
            return {SYNTAX_ERROR, EMPTY};
        return handle_get_list_of_files(user);
    }

    else if (command_parts[COMMAND] == CWD_COMMAND)
    {
        return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);
    }

    else if (command_parts[COMMAND] == RENAME_COMMAND)
    {
        if (command_parts.size() != 3)
            return {SYNTAX_ERROR, EMPTY};
        return handle_rename_file(command_parts[ARG1], command_parts[ARG2], user);
    }

    else if (command_parts[COMMAND] == RETR_COMMAND)
    {
        return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);
    }

    else if (command_parts[COMMAND] == HELP_COMMAND)
    {
        if (command_parts.size() != 1)
            return {SYNTAX_ERROR, EMPTY};
        return handle_help();
    }

    else if (command_parts[COMMAND] == QUIT_COMMAND)
    {
        if (command_parts.size() != 1)
            return {SYNTAX_ERROR, EMPTY};
        return handle_logout(user);
    }

    else
        return {SYNTAX_ERROR, EMPTY};
}

bool CommandHandler::is_a_file_name(string file_name)
{
    if (file_name.find(BACK_SLASH) != std::string::npos)
        return false;
    return true;
}

bool CommandHandler::user_has_access_to_file(string file_name, User *user)
{
    if (!UserManager::get_instance()->contains_as_special_file(file_name))
        return true;
    else if (user->is_able_to_access())
        return true;
    return false;
}

vector<std::string> CommandHandler::handle_username(string username, User *user)
{
    if (user->get_state() != User::State::WAITING_FOR_USERNAME)
        return {BAD_SEQUENCE, EMPTY};

    UserInfo *user_info = UserManager::get_instance()->get_user_info_by_username(username);

    if (user_info == nullptr)
        return {INVALID_USER_PASS, EMPTY};

    user->set_state(User::State::WAITING_FOR_PASSWORD);
    user->set_user_info(user_info);
    user->set_current_directory(ROOT);

    return {USERNAME_ACCEPTED, EMPTY};
}

vector<std::string> CommandHandler::handle_password(string password, User *user)
{
    if (user->get_state() != User::State::WAITING_FOR_PASSWORD)
        return {BAD_SEQUENCE, EMPTY};

    if (!user->get_user_info()->is_user_password(password))
        return {INVALID_USER_PASS, EMPTY};
    user->set_state(User::State::LOGGED_IN);
    Logger::get_instance()->log(user->get_username() + COLON + "logged in.");

    return {SUCCESSFUL_LOGIN, EMPTY};
}

vector<string> CommandHandler::handle_get_current_directory(User *user)
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

vector<string> CommandHandler::handle_create_new_directory(string dir_path, User *user)
{
    string bash_command = "mkdir " + user->get_current_directory() + dir_path;
    int status = system(bash_command.c_str());
    if (status == SUCCESS)
    {
        string message = COLON + dir_path + " created.";
        Logger::get_instance()->log(user->get_username() + message);
        return {CREATE_CODE + message, EMPTY};
    }
    return {GENERAL_ERROR, EMPTY};
}

vector<string> CommandHandler::handle_delete_directory(string dir_path, User *user)
{
    string bash_command = "rm -r " + user->get_current_directory() + dir_path;
    int status = system(bash_command.c_str());
    if (status == SUCCESS)
    {
        string message = COLON + dir_path + " deleted.";
        Logger::get_instance()->log(user->get_username() + message);
        return {DELETE_CODE + message, EMPTY};
    }
    return {GENERAL_ERROR, EMPTY};
}

vector<string> CommandHandler::handle_delete_file(string file_name, User *user)
{
    if (!is_a_file_name(file_name))
        return {SYNTAX_ERROR, EMPTY};

    if (!user_has_access_to_file(file_name, user))
        return {FILE_UNAVAILABLE, EMPTY};

    string bash_command = "rm " + user->get_current_directory() + file_name;
    int status = system(bash_command.c_str());
    if (status == SUCCESS)
    {
        string message = COLON + file_name + " deleted.";
        Logger::get_instance()->log(user->get_username() + message);
        return {DELETE_CODE + message, EMPTY};
    }
    return {GENERAL_ERROR, EMPTY};
}

vector<string> CommandHandler::handle_get_list_of_files(User *user)
{
    string bash_command = "ls " + user->get_current_directory() + " > file.txt";
    int status = system(bash_command.c_str());
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    string result = read_file_to_string("file.txt");
    result.pop_back();
    status = system("rm file.txt");
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    erase_sub_str(result, "file.txt\n");

    return {LIST_TRANSFER_DONE, result};
}

std::vector<std::string> CommandHandler::handle_change_working_directory(string dir_path, User *user)
{
    string check_validity_command = "realpath " + dir_path + " > file.txt";
    int status1 = system(check_validity_command.c_str());
    int status2 = system("rm file.txt");
    if (status1 != SUCCESS || status2 != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    if (dir_path == ROOT)
        user->set_current_directory(ROOT);
    else
        user->set_current_directory(user->get_current_directory() + dir_path + "/");

    return {SUCCESSFUL_CHANGE, EMPTY};
}

std::vector<std::string> CommandHandler::handle_rename_file(string old_name, string new_name, User *user)
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

std::vector<std::string> CommandHandler::handle_download_file(string file_name, User *user)
{
    if (!is_a_file_name(file_name))
        return {SYNTAX_ERROR, EMPTY};

    if (!user_has_access_to_file(file_name, user))
        return {FILE_UNAVAILABLE, EMPTY};

    string file_path = user->get_current_directory() + file_name;
    string size_command = "stat -c%s " + file_path + " > " + "size.txt";
    int status = system(size_command.c_str());
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    double file_size = read_file_to_double("size.txt");
    status = system("rm size.txt");
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    if (user->is_able_to_download(file_size) == false)
        return {DOWNLOAD_LIMIT_SIZE, EMPTY};

    string bash_command = "cp " + file_path + " file.txt";
    status = system(bash_command.c_str());
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    string result = read_file_to_string("file.txt");
    status = system("rm file.txt");
    if (status != SUCCESS)
        return {GENERAL_ERROR, EMPTY};

    user->decrease_available_size(file_size);

    string message = COLON + file_name + " downloaded.";
    Logger::get_instance()->log(user->get_username() + message);

    return {SUCCESSFUL_DOWNLOAD, result};
}

std::vector<std::string> CommandHandler::handle_help()
{
    string info = "214\n";
    info += USER_DESCRIPTION;
    info += PASS_DESCRIPTION;
    info += PWD_DESCRIPTION;
    info += MKD_DESCRIPTION;
    info += DELE_DESCRIPTION;
    info += LS_DESCRIPTION;
    info += CWD_DESCRIPTION;
    info += RENAME_DESCRIPTION;
    info += RETR_DESCRIPTION;
    info += HELP_DESCRIPTION;
    info += QUIT_DESCRIPTION;
    return {info, EMPTY};
}

vector<string> CommandHandler::handle_logout(User *user)
{
    if (user->get_state() != User::State::LOGGED_IN)
        return {GENERAL_ERROR, EMPTY};

    user->set_state(User::State::WAITING_FOR_USERNAME);

    Logger::get_instance()->log(user->get_username() + COLON + "logged out.");

    return {SUCCESSFUL_QUIT, EMPTY};
}
