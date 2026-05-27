#include "ResponseParser.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>

// function to read a single character from the socket
static bool readChar(int sockfd, char &c)
{
    ssize_t r = recv(sockfd, &c, 1, 0);
    return r == 1;
}

// function to read a line from the socket till a carriage return is encountered.
static std::string readLine(int sockfd)
{
    std::string line;
    char c;
    while (readChar(sockfd, c))
    {
        if (c == '\r')
        {
            // expect \n next; read and break
            readChar(sockfd, c);
            break;
        }
        line.push_back(c);
    }
    return line;
}

std::string ResponseParser::parseResponse(int sockfd)
{
    char prefix;
    if (!readChar(sockfd, prefix))
    {
        return ("(Error) No response or connection closed.");
    }

    // The first character returned by redis differs from type of item to item that is returned
    switch (prefix)
    {
    case '+':
        return parseSimpleString(sockfd);
        /* code */
        break;
    case '-':
        return parseSimpleErrors(sockfd);
        /* code */
        break;
    case ':':
        return parseInteger(sockfd);
        /* code */
        break;
    case '$':
        return parseBulkString(sockfd);
        /* code */
        break;
    case '*':
        return parseArray(sockfd);
        /* code */
        break;

    default:
        return "(Error) Unknown reply type.";
    }
}

std::string ResponseParser::parseSimpleString(int sockfd)
{
    return readLine(sockfd);
}


std::string ResponseParser::parseSimpleErrors(int sockfd)
{
    return "(Error) " + readLine(sockfd);
}


std::string ResponseParser::parseInteger(int sockfd)
{
    return readLine(sockfd);
}


std::string ResponseParser::parseBulkString(int sockfd)
{
    std::string lengthStr = readLine(sockfd);
    int length = std::stoi(lengthStr);
    if (length == -1)
    {
        return "(nil)";
    }

    std::string bulk;
    bulk.resize(length);
    int totalRead = 0;
    while (totalRead < length)
    {
        ssize_t r = recv(sockfd, &bulk[totalRead], length - totalRead, 0);
        if (r <= 0)
        {
            return "(Error) Incomplete bulk data.";
        }

        totalRead += r; // update total bytes read
    }

    // Consume trailing CRLF
    char dummy;
    readChar(sockfd, dummy); // \r
    readChar(sockfd, dummy); // \n

    return bulk;
};


std::string ResponseParser::parseArray(int sockfd)
{
    std::string countStr = readLine(sockfd);
    int count = std::stoi(countStr);
    if (count == -1)
    {
        return "(nil)";
    }

    std::ostringstream oss;
    for (int i = 0; i < count; i++)
    {
        oss << parseResponse(sockfd);
        if (i != count - 1)
        {
            oss << "\n";
        }
    }

    return oss.str();
}