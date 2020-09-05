#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception {
    std::string message;
public:
    Exception(std::string message);
    std::string getMessage();
};

#endif

