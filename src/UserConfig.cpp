#include "UserConfig.hpp"
#include <sstream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

using namespace std;
using namespace rapidjson;

UserConfig::UserConfig(const std::string path)
{
  ifstream f(path);
  stringstream buf;
  buf << f.rdbuf();
  Document root_dom;
  root_dom.Parse(buf.str().c_str());
  auto users_tree = root_dom["users"].GetArray();

  for (auto &item : users_tree)
  {
    string name = item["name"].GetString();
    string password = item["password"].GetString();
    bool is_admin = item["is_admin"].GetBool();
    double size = item["size"].GetDouble();
    users_info.push_back(new UserInfo(name, password, is_admin, size));
  }

  for (auto &value : root_dom["files"].GetArray())
    files.push_back(value.GetString());
}

std::vector<std::string> UserConfig::get_files()
{
  return files;
}

std::vector<UserInfo *> UserConfig::get_users_info()
{
  return users_info;
}
