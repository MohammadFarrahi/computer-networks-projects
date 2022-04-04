#include "Utilities.hpp"

#include <iostream>

using namespace std;

void erase_sub_str(std::string & main_str, const std::string & to_erase)
{
    size_t pos = main_str.find(to_erase);
    if (pos != std::string::npos) {
        main_str.erase(pos, to_erase.length());
    }
}

string read_file_as_binary(string file_path) {
    ifstream t(file_path, std::ios::binary);
    string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    t.close();
    return str;
}
void write_file_as_binary(string file_path, char* input_data) {
    std::ofstream output(file_path, std::ios::binary);
    string input_as_string(input_data);
    output << input_as_string;
    output.close();
}

vector<string> parse_command(char* input) {
    vector<string> info;
    
    char * copy = (char*)malloc(strlen(input) + 1); 
    strcpy(copy, input);
    char *token = strtok(copy, " "); 
   
    while (token != NULL) {
        info.push_back(token);
        token = strtok(NULL, " ");
    }
    free(copy);
    return info;
}

pair<int, string> exec_command(string cmd) {

  int status;
  string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    status = WEXITSTATUS(pclose(stream));
  }
  return {status, data.substr(0, data.size() - 1)};
}

double get_file_size(string file_path){
    string size_command = "stat -c%s " + file_path;
    auto file_size_info = exec_command(size_command);
    if (file_size_info.first != 0)
        return -1.0;
    double file_size = stod(file_size_info.second);
    return file_size;
}
