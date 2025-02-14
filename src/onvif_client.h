#ifndef ONVIF_CLIENT_H
#define ONVIF_CLIENT_H

#include <string>

class ONVIFClient {
public:
    ONVIFClient(const std::string& protocol, const std::string& addr, const std::string& username, const std::string& password);
    std::string getMetadataStreamUri();

private:
    std::string protocol;
    std::string addr;
    std::string username;
    std::string password;
};

#endif // ONVIF_CLIENT_H
