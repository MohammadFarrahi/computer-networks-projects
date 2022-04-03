#include "CommandHandler/ICommand.hpp"
using namespace std;

bool ICommandHandler::is_a_file_name(string file_name) {
    if (file_name.find(BACK_SLASH) != std::string::npos)
        return false;
    return true;
}

bool ICommandHandler::user_has_access_to_file(string file_name, User* user) {
    if (!UserManager::get_instance()->contains_as_special_file(file_name))
        return true;
    else if (user->is_able_to_access())
        return true;
    return false;
}