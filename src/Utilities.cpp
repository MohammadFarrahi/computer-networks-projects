#include "Utilities.hpp"

using namespace std;

void erase_sub_str(std::string & main_str, const std::string & to_erase)
{
    size_t pos = main_str.find(to_erase);
    if (pos != std::string::npos) {
        main_str.erase(pos, to_erase.length());
    }
}

std::string read_file_to_string(std::string file_path) {
    std::ifstream t(file_path);
    std::string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

double read_file_to_double(std::string file_path) {
    std::ifstream ifile(file_path, std::ios::in);
    double data;
    ifile >> data;
    return data;
}

vector<string> parse_command(char* input) {
    vector<string> info;
    char *token = strtok(input, " "); 
   
    while (token != NULL) {
        info.push_back(token);
        token = strtok(NULL, " ");
    }
    return info;
}
