#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <iostream>
#include <string>

class HTTPClient {
public:
    static bool checkAIStatus(const std::string& url);
    static void sendCommand(const std::string& url, const std::string& param);
};

#endif // HTTP_CLIENT_H
