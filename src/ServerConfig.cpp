#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "ServerConfig.hpp"
#include <fstream>
#include <sstream>

using namespace rapidjson;
using namespace std;


ServerConfig::ServerConfig(const string path) {
    ifstream f(path); stringstream buf; buf << f.rdbuf();
    Document root_dom; root_dom.Parse(buf.str().c_str());

    command_channel_port = root_dom["commandChannelPort"].GetInt();
    data_channel_port = root_dom["dataChannelPort"].GetInt();

    // pt::ptree users_tree = root_tree.get_child("users");
    // for (auto& item : users_tree.get_child("")) {
    //     string name = item.second.get<string>("user");
    //     string password = item.second.get<string>("password");
    //     bool is_admin = item.second.get<bool>("admin");
    //     double size = item.second.get<double>("size");
        
    //     users_identity_info.push_back(new UserIdentityInfo(name, password, is_admin, size));
    // }
    for (auto& value : root_dom["files"].GetArray())
        files.push_back(value.GetString());

}

int ServerConfig::get_command_channel_port() {
    return command_channel_port;
}

int ServerConfig::get_data_channel_port() {
    return data_channel_port;
}

std::vector<std::string> ServerConfig::get_files() {
    return files;
}

// testing

// #include <iostream>
// int main() {
//     auto conf = new ServerConfig("config.json");
//     cout << conf->get_command_channel_port() << endl;
//     cout << conf->get_data_channel_port() << endl;
//     cout << conf->get_files()[0] << endl;
//     return 0;
// }
