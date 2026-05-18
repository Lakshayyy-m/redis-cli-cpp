#ifndef RedisClient_H
#define RedisClient_H

#include <string>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h> 

class RedisClient
{
public:
    RedisClient(const std::string &host, int port);
    ~RedisClient();

    bool connectToServer();
    void disconnect();

private:
    std::string host;
    int port;
    int sockfd;
};

#endif