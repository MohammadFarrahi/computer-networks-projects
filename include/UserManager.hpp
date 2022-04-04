#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "UserConfig.hpp"
#include "UserInfo.hpp"
#include "User.hpp"

#include <vector>
#include <algorithm>

#include "Constants.hpp"

class UserManager
{
public:

    ~UserManager();
    static UserManager* get_instance();

    void add_user(int command_socket, int data_socket);
    void remove_user(int socket);

    User* get_user_by_socket(int socket);

    UserInfo* get_user_info_by_username(std::string username);

    bool contains_as_special_file(std::string file_path);

private:
    UserManager(UserConfig user_config);
    std::vector<UserInfo*> users_info;
    std::vector<User*> users;

    static UserManager* instance;

    std::vector<std::string> files;
};

#endif