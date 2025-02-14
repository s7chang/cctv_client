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
    virtual bool readConfig(const std::string& param, std::string& response) const noexcept(false) = 0;
    virtual bool writeConfig(const std::string& param, const std::string& value) const noexcept(false) = 0;

    bool readConfigBool(const std::string& param) const noexcept(false);
    int readConfigInt(const std::string& param) const noexcept(false);
    std::string readConfigString(const std::string& param) const noexcept(false);

    inline void writeConfigBool(const std::string& param, bool value) const noexcept(false) { writeConfig(param, value ? "1" : "0"); }
    inline void writeConfigInt(const std::string& param, int value) const noexcept(false) { writeConfig(param, std::to_string(value)); }
    inline void writeConfigString(const std::string& param, const std::string& value) const noexcept(false) { writeConfig(param, value); }
};

#endif // CAMERA_H
