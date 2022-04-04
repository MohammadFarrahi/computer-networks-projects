#include "User.hpp"

using namespace std;

User::User(int command_socket, int data_socket)
: command_socket(command_socket)
, data_socket(data_socket)
, state(WAITING_FOR_USERNAME)
, current_directory(Constant::ROOT)
, user_info(nullptr) {
}

int User::get_command_socket() {
    return command_socket;
}

int User::get_data_socket() {
    return data_socket;
}

User::State User::get_state() {
    return state;
}

string User::get_username() {
    return user_info->get_username();
}

string User::get_current_directory() {
    return current_directory;
}

UserInfo* User::get_user_info() {
    return user_info;
}

void User::set_state(User::State _state) {
    state = _state;
}

void User::set_user_info(UserInfo* _user_info) {
    user_info = _user_info;
}

void User::set_current_directory(string path) {
    current_directory = path;
}

bool User::is_able_to_download(double file_size) {
    if (user_info->get_available_size() >= file_size/1000)
        return true;
    return false;
}

void User::decrease_available_size(double file_size) {
   user_info->decrease_available_size(file_size);
}

bool User::is_able_to_access() {
    return user_info->is_admin_user();
}