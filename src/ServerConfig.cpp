#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "ServerConfig.hpp"
#include <fstream>
#include <sstream>

using namespace rapidjson;
using namespace std;

ServerConfig::ServerConfig(const string path)
{
    ifstream f(path);
    stringstream buf;
    buf << f.rdbuf();
    Document root_dom;
    root_dom.Parse(buf.str().c_str());

    command_channel_port = root_dom["commandChannelPort"].GetInt();
    data_channel_port = root_dom["dataChannelPort"].GetInt();
}

int ServerConfig::get_command_channel_port()
{
    return command_channel_port;
}

int ServerConfig::get_data_channel_port()
{
    return data_channel_port;
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