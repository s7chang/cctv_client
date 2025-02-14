#include "camera.h"
#include <iostream>
#include <sstream>

bool Camera::readConfigBool(const std::string& param) const {
    std::string response;
    if (!readConfig(param, response)) {
        std::cerr << "Failed to read config for param: " << param << std::endl;
        return false; // 기본값 반환
    }

    // 응답이 "1"이면 true, 아니면 false 반환
    return response == "1";
}

int Camera::readConfigInt(const std::string& param) const {
    std::string response;
    if (!readConfig(param, response)) {
        std::cerr << "Failed to read config for param: " << param << std::endl;
        return -1; // 실패 시 기본값
    }

    try {
        return std::stoi(response); // 문자열을 정수로 변환
    } catch (const std::exception& e) {
        std::cerr << "Error parsing int from response: " << response << " (" << e.what() << ")" << std::endl;
        return -1;
    }
}

std::string Camera::readConfigString(const std::string& param) const {
    std::string response;
    if (!readConfig(param, response)) {
        std::cerr << "Failed to read config for param: " << param << std::endl;
        return ""; // 실패 시 빈 문자열 반환
    }
    return response;
}
