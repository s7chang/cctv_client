#ifndef CAMERA_H
#define CAMERA_H

#include "http_client.h"
#include <string>

class Camera {
public:
    Camera(const std::string& cameraIp, int port = 80, const std::string& protocol = "http") : protocol(protocol), addr(cameraIp + ":" + std::to_string(port)) {}
    virtual ~Camera() {}

protected:
    std::string protocol;
    std::string addr;

    // 설정
    virtual bool readConfig(const std::string& param, std::string& response) const = 0;
    virtual bool writeConfig(const std::string& param, const std::string& value) const = 0;

    bool readConfigBool(const std::string& param) const;
    int readConfigInt(const std::string& param) const;
    std::string readConfigString(const std::string& param) const;
};

#endif // CAMERA_H
