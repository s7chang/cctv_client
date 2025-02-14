#ifndef HTTP_EXCEPTION_H
#define HTTP_EXCEPTION_H

#include <stdexcept>

class HttpException : public std::runtime_error {
public:
    HttpException(const std::string& message, int code)
        : std::runtime_error(message), httpCode(code) {}

    int getHttpCode() const { return httpCode; }

private:
    int httpCode;
};

#endif // HTTP_EXCEPTION_H
