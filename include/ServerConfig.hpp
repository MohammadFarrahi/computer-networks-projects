#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <vector>


class ServerConfig {
public:
    ServerConfig(const std::string path);

    int get_command_channel_port();
    int get_data_channel_port();
    std::vector<std::string> get_files();

private:
    int command_channel_port;
    int data_channel_port;
    std::vector<std::string> files;
};

#endif