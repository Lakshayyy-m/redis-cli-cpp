#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include <regex>

class CommandHandler {
    public:
    // Split args into tokens
    static std::vector<std::string> splitArgs(const std::string &input);


};

#endif