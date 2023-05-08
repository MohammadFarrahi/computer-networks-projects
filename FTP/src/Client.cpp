#include "Client.hpp"

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

using namespace std;

int connect_channel_to_server(int port, string ip){
    int channel_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr) <= 0)
        return -1;
    if (connect(channel_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        return -1;
    return channel_fd;
}

void Client::start(int command_channel_port, int data_channel_port) {
    int client_command_fd, client_data_fd;
    client_command_fd = connect_channel_to_server(command_channel_port, "127.0.0.1");
    client_data_fd = connect_channel_to_server(data_channel_port, "127.0.0.1");

    if (client_command_fd < 0 || client_data_fd < 0){
        cout << "Could not connect to server" << endl;
        return;    
    }

    char received_command_output[2048] = {0};
    char received_data_output[4048] = {0};
    while (true) {
        // Read command from CLI.
        cout << "> ";
        char command[MAX_COMMAND_LENGTH];
        memset(command, 0, MAX_COMMAND_LENGTH);
        cin.getline (command, MAX_COMMAND_LENGTH);
        auto command_parts = parse_command(command);

        // Send command to server.
        send(client_command_fd, command, MAX_COMMAND_LENGTH, 0);

        // Receive command output.
        memset(received_command_output, 0, sizeof received_command_output);
        recv(client_command_fd, received_command_output, sizeof(received_command_output), 0);
        cout << "Command output: " << received_command_output << endl;

        // Receive data output.
        memset(received_data_output, 0, sizeof received_data_output);
        recv(client_data_fd, received_data_output, sizeof(received_data_output), 0);
        if(command_parts[COMMAND] == "retr" && string(received_data_output).size() > 1){
            write_file_as_binary(command_parts[ARG1], received_data_output);
        }
        else
            cout << "Data output: " << received_data_output << endl;
    }
}

int main() {
    // const string config_file_path = "./configuration/config.json";
    // ServerConfig server_config(config_file_path);
    Client client;
    // client.start(server_config.get_command_channel_port(), server_config.get_data_channel_port());
    client.start(8000, 8001);
    return 0;
}
