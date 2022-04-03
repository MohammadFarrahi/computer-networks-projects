#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <cstring>

std::string read_file_to_string(std::string file_path);
double read_file_to_double(std::string file_path);
std::vector<std::string> parse_command(char* input);
void erase_sub_str(std::string & main_str, const std::string & to_erase);

#endif
