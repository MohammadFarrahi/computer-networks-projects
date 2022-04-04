#include "Server.hpp"

using namespace std;

Server::Server(ServerConfig server_config, UserConfig user_config)
: command_channel_port(server_config.get_command_channel_port())
, data_channel_port(server_config.get_data_channel_port()) {
    command_handler = new CommandHandler(user_config);
}

Server::~Server() {
    delete command_handler;
}

int Server::setup_channel(int port) {
    int channel_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(channel_fd < 0)
        return -1;
    int opt = 1;
    if (setsockopt(channel_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return -1;

    struct sockaddr_in socket_addr;
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = INADDR_ANY;
    socket_addr.sin_port = htons(port);        

    if (bind(channel_fd, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) < 0) 
        return -1;
    
    constexpr int backlog = 10;
    if (listen(channel_fd, backlog) < 0)
        return -1;
    
    return channel_fd;
}

int Server::accept_new_client(int command_fd, int data_fd, fd_set& copy_fds) {
    int new_command_socket = accept(command_fd, NULL, NULL);
    int new_data_socket = accept(data_fd, NULL, NULL);

    if (new_command_socket < 0 || new_data_socket < 0)
        return -1;
    
    UserManager::get_instance()->add_user(new_command_socket, new_data_socket);
    FD_SET(new_command_socket, &copy_fds);
    return new_command_socket;
}

void Server::send_response_to_client(int fd, vector<string> response) {
    send(fd , response[COMMAND].c_str() , response[COMMAND].size() , 0);
    send(UserManager::get_instance()->get_user_by_socket(fd)->get_data_socket(),
            response[CHANNEL].c_str() , response[CHANNEL].size() , 0);
}

void Server::close_connection(int fd){
    close(fd);
    close(UserManager::get_instance()->get_user_by_socket(fd)->get_data_socket());
    UserManager::get_instance()->remove_user(fd);
}

void Server::start() {
    int command_server_fd, data_server_fd;

    command_server_fd = setup_channel(command_channel_port);
    data_server_fd = setup_channel(data_channel_port);

    if (command_server_fd < 0 || data_server_fd < 0){
        cout << "Could not setup server" << endl;
        return;
    }

    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(command_server_fd, &copy_fds);
    int max_fd = command_server_fd;
    int activity;
    char received_buffer[128] = {0};

    cout << "server starting ..." << endl;

    while (true) {
        // Add sockets to set
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds));

        // Select
        int ready_sockets = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (ready_sockets < 0)
            return;

        // int ready_sockets = activity;
        for (int fd = 0; fd <= max_fd  &&  ready_sockets > 0; ++fd) {
            if (FD_ISSET(fd, &read_fds)) {
                // New connection.
                if (fd == command_server_fd) {
                    int new_command_socket = accept_new_client(command_server_fd, data_server_fd, copy_fds);
                    if(new_command_socket < 0)
                        return;

                    if (new_command_socket > max_fd )
                        max_fd = new_command_socket;
                }

                // New readable socket.
                else {
                    bool has_closed = false;
                    memset(received_buffer, 0, sizeof received_buffer);
                    int result = recv(fd, received_buffer, sizeof(received_buffer), 0);

                    if (result < 0)
                        if (errno != EWOULDBLOCK)
                            has_closed = true;

                    // Check for close connection from client
                    if (result == 0)
                        has_closed = true;

                    // Data is received.
                    if (result > 0) {
                        vector<string> output = command_handler->do_command(fd, received_buffer);
                        send_response_to_client(fd, output);
                    }

                    if (has_closed) {
                        close_connection(fd);
                        FD_CLR(fd, &copy_fds);
                        if (fd == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }
        cout << "\tAn event has accured ...\t" << endl;
    }
}

int main() {
    const string config_file_path = "configuration/config.json";
    ServerConfig server_config(config_file_path);
    UserConfig user_config(config_file_path);
    Server server(server_config, user_config);
    server.start();
    return 0;
}
