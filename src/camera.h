#ifndef CAMERA_H
#define CAMERA_H

#include "http_client.h"
#include <string>
#include <list>
#include <sstream>

struct POINT {
    int x;
    int y;
};

// 요일: 0=일, 1=월, ..., 6=토
enum E_WeekDay { 
    SUN, MON, TUE, WED, THU, FRI, SAT,
};
std::string to_string(E_WeekDay weekDay);

// Object (X로 표기)
enum E_Object {
    PERSON, BICYCLE, CAR, 
};
std::string to_string(E_Object objectType);

// Behavior (B로 표기)
enum E_Behavior {
    APPEAR, STAY, DIRECTION, ENTER, EXIT, LOITERING, FALLDOWN, FIGHT,
};
std::string to_string(E_Behavior behavior);

// EventAction (표기 생략)
enum E_EventAction {
    ALARM, EMAIL, FTP, PRESET, HTTPACTION, EVENTOSD,
};
std::string to_string(E_EventAction behavior);

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
    std::list<POINT> readConfigPoints(const std::string& param) const noexcept(false);

    inline void writeConfigBool(const std::string& param, bool value) const noexcept(false) { writeConfig(param, value ? "1" : "0"); }
    inline void writeConfigInt(const std::string& param, int value) const noexcept(false) { writeConfig(param, std::to_string(value)); }
    inline void writeConfigString(const std::string& param, const std::string& value) const noexcept(false) { writeConfig(param, value); }
    void writeConfigPoints(const std::string& param, const std::list<POINT>& points) const noexcept(false);
};

#endif // CAMERA_H
