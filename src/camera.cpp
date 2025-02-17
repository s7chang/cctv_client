#include "camera.h"
#include <iostream>
#include <sstream>


std::string to_string(E_WeekDay weekDay) {
    static const std::string weekDays[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    return weekDays[weekDay];
}

std::string to_string(E_Object objectType) {
    static const std::string objectNames[] = { "PERSON", "BICYCLE", "CAR" };
    return objectNames[objectType];
}

std::string to_string(E_Behavior behavior) {
    static const std::string behaviors[] = { "APPEAR", "STAY", "DIRECTION", "ENTER", "EXIT", "LOITERING", "FALLDOWN", "FIGHT" };
    return behaviors[behavior];
}

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

std::list<POINT> Camera::readConfigPoints(const std::string& param) const {
    std::list<POINT> points;

    // URL 인코딩된 좌표 데이터를 읽어서 디코딩
    std::string decodedPositions = HttpClient::urlDecode(readConfigString(param));

    // ','를 기준으로 직접 문자열을 쪼개기
    size_t start = 0, end;
    POINT point;
    int count = 0;

    while ((end = decodedPositions.find(',', start)) != std::string::npos) {
        std::string token = decodedPositions.substr(start, end - start);
        if (count % 2 == 0) {
            point.x = std::stoi(token);
        } else {
            point.y = std::stoi(token);
            points.push_back(point);
        }
        count++;
        start = end + 1;
    }

    return points;
}

void Camera::writeConfigPoints(const std::string& param, const std::list<POINT>& points) const {
    std::string values;
    for (auto pt : points) {
        values += std::to_string(pt.x) + "," + std::to_string(pt.y) + ",";
    }
    values.pop_back();       // 마지막 , 제거. points가 0개라면 죽는다
    writeConfigString(param, HttpClient::urlEncode(values));
}
