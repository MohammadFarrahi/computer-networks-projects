#include "UserInfo.hpp"

using namespace std;

UserInfo::UserInfo(string _username, string _password, bool _is_admin, double _available_size)
: username(_username)
, password(_password)
, is_admin(_is_admin)
, available_size(_available_size) {
}

bool UserInfo::is_valid_credential(string _username, string _password) {
    if (username == _username && password == _password)
        return true;
    return false;
}

bool UserInfo::is_admin_user() {
    return is_admin;
}

std::string UserInfo::get_username() {
    return username;
}

// std::string UserInfo::get_password() {
//     return password;
// }

double UserInfo::get_available_size() {
    return available_size;
}

void UserInfo::decrease_available_size(double file_size) {
   available_size -= (file_size/1000);
}