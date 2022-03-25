#include "UserModel.hpp"

using namespace std;

UserModel::UserModel(string _username, string _password, bool _is_admin, double _available_size)
: username(_username)
, password(_password)
, is_admin(_is_admin)
, available_size(_available_size) {
}

bool UserModel::is_valid_credential(string _username, string _password) {
    if (username == _username && password == _password)
        return true;
    return false;
}

bool UserModel::is_admin_user() {
    return is_admin;
}

std::string UserModel::get_username() {
    return username;
}

std::string UserModel::get_password() {
    return password;
}

double UserModel::get_available_size() {
    return available_size;
}

void UserModel::decrease_available_size(double file_size) {
   available_size -= (file_size/1000);
}