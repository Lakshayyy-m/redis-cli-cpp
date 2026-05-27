#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include <regex>
#include <sstream>


class CommandHandler
{
public:
    // Split args into tokens
    static std::vector<std::string> splitArgs(const std::string &input);

    // Build RESP comand  from the input vector arguments
    static std::string buildRESPcommand(const std::vector<std::string> &args);
};

#endif