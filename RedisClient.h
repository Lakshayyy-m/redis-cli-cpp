#ifndef RedisClient_H
#define RedisClient_H

class RedisClient {
public:
    RedisClient(const std::string &host, int port);
    ~RedisClient();

    bool connectToServer();

private:
    std::string host;
    int port;
    int sockfd;
};

#endif