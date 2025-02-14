#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <functional>
#include <curl/curl.h>

class HttpClient {
public:
    static bool sendRequest(const std::string& protocol, const std::string& method, const std::string& url, std::string* response = nullptr);
};

#endif // HTTP_CLIENT_H
