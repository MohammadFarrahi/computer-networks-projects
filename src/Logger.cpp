
#include "Logger.hpp"

using namespace std;

Logger* Logger::instance = NULL;

Logger::Logger(string path)
: path(path) {
    fstream log_file;
    log_file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!log_file) {
        cout << "Cannot open file, log file does not exist. Creating new file..";
        log_file.open(path,  fstream::in | fstream::out | fstream::trunc);
        log_file.close();
    } 
}

Logger* Logger::get_instance(){
    if(instance==NULL){
        instance = new Logger(LOG_FILE);
    }
    return instance;
}

void Logger::log(string message) {
     fstream log_file;
     log_file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
     
     auto curr = std::chrono::system_clock::now();
     std::time_t curr_time = std::chrono::system_clock::to_time_t(curr);
     
     log_file << std::ctime(&curr_time);
     log_file << message << endl;
     log_file.close();
}
