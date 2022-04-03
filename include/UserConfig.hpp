#ifndef USER_CONFIG_HPP
#define USER_CONFIG_HPP

#include <string>
#include <vector>
#include "UserInfo.hpp"

class UserConfig
{
public:
  UserConfig(const std::string path);
  std::vector<UserInfo *> get_users_info();
  std::vector<std::string> get_files();

private:
  std::vector<UserInfo *> users_info;
  std::vector<std::string> files;
};

#endif