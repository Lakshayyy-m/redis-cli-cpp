#include "CLI.h"
#include <string>

static std::string trim(std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

CLI::CLI(const std::string &host, int port) : redisClient(host, port) {}

void CLI::run()
{
    if (!redisClient.connectToServer())
    {
        return;
    }

    std::cout << "Connected to Redis at:" << redisClient.getSocketFD() << " \n";

    while (true)
    {
        std::cout << redisClient.getHost() << ":" << redisClient.getPort() << "> ";
        std::cout.flush();
        std::string line;
        if (!std::getline(std::cin, line))
            break;
        line = trim(line);
        if (line.empty())
            continue;
        if (line == "quit")
        {
            std::cout << "Quitting....";
            break;
        }

        if (line == "help")
        {
            std::cout << "Displaying help....\n";
            continue;
        }

        // Split commands into tokens
        std::vector <std::string> args = CommandHandler::splitArgs(line);

        if(args.empty()) continue;

        // for(const auto &arg : args) {
        //     std::cout << arg << "\n";

        // }
        std::string command = CommandHandler::buildRESPcommand(args);
        if(!redisClient.sendCommand(command)) {
            std::cerr << "(Error) Failed to send the command.\n";
            break;
        }

        // Parse and print repsonse                                    
    }
}