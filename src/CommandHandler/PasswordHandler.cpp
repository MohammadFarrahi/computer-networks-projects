#include "CommandHandler/PasswordHandler.hpp"

using namespace std;

vector<std::string> PasswordHandler::handle_password(string password, User *user)
{
    if (user->get_state() != User::State::WAITING_FOR_PASSWORD)
        return {BAD_SEQUENCE, EMPTY};

    if (!user->get_user_info()->is_user_password(password))
        return {INVALID_USER_PASS, EMPTY};
    user->set_state(User::State::LOGGED_IN);
    // logger->log(user->get_username() + COLON + "logged in.");

    return {SUCCESSFUL_LOGIN, EMPTY};
}

vector<string> PasswordHandler::handle_command(const vector<string> command_parts, User *user)
{
    if (command_parts.size() != 2)
        return {SYNTAX_ERROR, EMPTY};
    return handle_password(command_parts[ARG1], user);
}
