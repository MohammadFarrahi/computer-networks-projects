#ifndef CONST_HPP
#define CONST_HPP

#include <string>
#include "Utilities.hpp"

#define COMMAND 0
#define CHANNEL 1
#define ARG1 1
#define ARG2 2
#define SUCCESS 0
#define EMPTY " "
#define COLON ": "
#define BACK_SLASH "/"
#define SLASH '/'

class Constant {
public:
    static std::string ROOT;
};

#endif