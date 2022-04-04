#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <cstdlib>

std::string read_file_as_binary(std::string file_path);
void write_file_as_binary(std::string file_path, char* input_data);
std::vector<std::string> parse_command(char* input);
void erase_sub_str(std::string & main_str, const std::string & to_erase);
std::pair<int, std::string> exec_command(std::string cmd);

#endif
