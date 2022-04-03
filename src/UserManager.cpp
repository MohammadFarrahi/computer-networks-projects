#include "UserManager.hpp"

using namespace std;

UserManager::UserManager(UserConfig user_config)
: users_info(user_config.get_users_info())
, files(user_config.get_files()) {
}
UserManager::~UserManager() {
    for (auto u : users_info)
        delete u;
    users_info.clear();

    for (auto u : users)
        delete u;
    users.clear();
}

void UserManager::add_user(int command_socket, int data_socket) {
    users.push_back(new User(command_socket, data_socket));
}

void UserManager::remove_user(int socket) {
    for(size_t i = 0; i < users.size(); ++i) {
        if (users[i]->get_command_socket() == socket) {
            users.erase(users.begin() + i);
            break;
        }
    }
}

User* UserManager::get_user_by_socket(int socket) {
    for(size_t i = 0; i < users.size(); ++i)
        if (users[i]->get_command_socket() == socket)
            return users[i];
    return nullptr;
}

UserInfo* UserManager::get_user_info_by_username(string username) {
    for(size_t i = 0; i < users_info.size(); ++i)
        if (users_info[i]->get_username() == username)
            return users_info[i];
    return nullptr;
}

bool UserManager::contains_as_special_file(string filename) {
    for (size_t i = 0; i < files.size(); i++) {
        if (files[i] == filename)
            return true;
    }
    return false;
}

