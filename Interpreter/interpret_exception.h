#pragma once
#include <exception>
#include <string>

struct debugInfo {
    int row = -1;
    int col = -1;
};

struct MyInterpretException : public std::exception
{
    debugInfo debugInfo;
    std::string msg;
    const char * what() const throw () {
        return msg.c_str();
    }
    
    MyInterpretException(std::string msg) : msg(msg) {}
    MyInterpretException(std::string msg, debugInfo debugInfo) : msg(msg), debugInfo(debugInfo) {}
    MyInterpretException(std::string msg, int row, int col) : msg(msg), debugInfo({row, col}) {}
};