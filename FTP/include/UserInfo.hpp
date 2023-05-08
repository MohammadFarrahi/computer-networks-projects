#ifndef UserInfo_HPP
#define UserInfo_HPP

#include <iostream>
#include <string>

class UserInfo {
public:
    UserInfo(std::string _username, std::string _password, bool _is_admin, double _available_size);
    bool is_valid_credential(std::string _username, std::string _password);
    bool is_admin_user();
    void decrease_available_size(double file_size);

    std::string get_username();
    bool is_user_password(std::string _password);
    double get_available_size();

private:
    std::string username;
    std::string password;
    bool is_admin;
    double available_size;
};

#endif
