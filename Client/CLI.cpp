#include "CLI.h"
#include <string>

CLI::CLI(const std::string &host, int port) : redisClient(host, port) {}

void CLI::run()
{
    if (!redisClient.connectToServer())
    {
        return;
    }

    std::cout << "Connected to Redis at: \n"; 
}