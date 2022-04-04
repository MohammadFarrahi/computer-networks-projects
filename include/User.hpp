#ifndef USER_HPP
#define USER_HPP

#include "UserInfo.hpp"

#include <iostream>
#include <string>

#include "Constants.hpp"

class User {
public:
    enum State {
        WAITING_FOR_USERNAME,
        WAITING_FOR_PASSWORD,
        LOGGED_IN,
    };

    User(int command_socket, int data_socket);

    int get_command_socket();
    int get_data_socket();
    State get_state();
    std::string get_username();
    std::string get_current_directory();
    UserInfo* get_user_info();

    void set_state(State _state);
    void set_user_info(UserInfo* _user_info);
    void set_current_directory(std::string path);
    void decrease_available_size(double file_size);

    bool is_able_to_download(double file_size);
    bool is_able_to_access();

private:
    int command_socket;
    int data_socket;
    State state;
    std::string current_directory;
    UserInfo* user_info;
};

#endif
