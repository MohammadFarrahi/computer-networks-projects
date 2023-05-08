#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <string>
#include <vector>


class ServerConfig {
public:
    ServerConfig(const std::string path);

    int get_command_channel_port();
    int get_data_channel_port();

private:
    int command_channel_port;
    int data_channel_port;
};

#endif