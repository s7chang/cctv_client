#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <functional>
#include <curl/curl.h>

class HttpClient {
public:
    static bool sendRequest(const std::string& protocol, const std::string& method, const std::string& url, const std::string& username, const std::string& passwd, std::string* response = nullptr) noexcept(false);

    static std::string urlDecode(const std::string& encoded);
    static std::string urlEncode(const std::string& value);
};

#endif // HTTP_CLIENT_H
