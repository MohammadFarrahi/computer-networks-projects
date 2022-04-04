#ifndef SERVER_H_
#define SERVER_H_

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "Constants.hpp"
#include "ServerConfig.hpp"
#include "UserConfig.hpp"
#include "CommandHandler.hpp"
#include "Logger.hpp"
#include <utility>


class Server {
public:
    Server(ServerConfig server_config, UserConfig user_config);

    ~Server();
    void start();

private:
    CommandHandler* command_handler;
    int setup_channel(int port);
    int accept_new_client(int command_fd, int data_fd, fd_set& copy_fds);
    void send_response_to_client(int fd, std::vector<std::string> response);
    void close_connection(int fd);





    int command_channel_port;
    int data_channel_port;
};

#endif
