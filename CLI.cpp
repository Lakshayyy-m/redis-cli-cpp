#include "CLI.h"
#include <string>

CLI::CLI(const std::string &host, int port) : redisClient(host, port) {} 