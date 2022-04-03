#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

#define LOG_FILE "log.txt"


class Logger
{
public:
    void log(std::string message);
    static Logger *get_instance();

private:
    Logger(std::string path);
    std::string path;
    static Logger *instance;
};

#endif
