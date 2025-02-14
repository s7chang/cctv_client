#ifndef CAMERA_TRUEN_H
#define CAMERA_TRUEN_H

#include <list>
#include <sstream>

#include "camera.h"

struct POINT {
    int x;
    int y;
};

class CameraTruen : public Camera {
public:
    CameraTruen(const std::string& cameraIp, int port = 80, const std::string& protocol = "http") : Camera(cameraIp, port, protocol) {}

    // 객체 탐지 (Object Detection)
    void setObjectDetection(bool enable) { writeConfigBool("AIX_OBJECT_DETECTION_ENABLE", enable); }
    bool getObjectDetection() { return readConfigBool("AIX_OBJECT_DETECTION_ENABLE"); }

    // 특정 객체 탐지
    void setPersonDetection(bool enable) { writeConfigBool("AIX_PERSON_DETECTION_ENABLE", enable); }
    bool getPersonDetection() { return readConfigBool("AIX_PERSON_DETECTION_ENABLE"); }
    
    void setBicycleDetection(bool enable) { writeConfigBool("AIX_BICYCLE_DETECTION_ENABLE", enable); }
    bool getBicycleDetection() { return readConfigBool("AIX_BICYCLE_DETECTION_ENABLE"); }
    
    void setCarDetection(bool enable) { writeConfigBool("AIX_CAR_DETECTION_ENABLE", enable); }
    bool getCarDetection() { return readConfigBool("AIX_CAR_DETECTION_ENABLE"); }

    // 객체 디스플레이 방식 (0: off, 1: Bounding Box, 2: Blur)
    void setPersonDisplayType(int type) { writeConfigInt("AIX_PERSON_DISPLAY_TYPE", type); }
    int getPersonDisplayType() { return readConfigInt("AIX_PERSON_DISPLAY_TYPE"); }
    
    void setBicycleDisplayType(int type) { writeConfigInt("AIX_BICYCLE_DISPLAY_TYPE", type); }
    int getBicycleDisplayType() { return readConfigInt("AIX_BICYCLE_DISPLAY_TYPE"); }
    
    void setCarDisplayType(int type) { writeConfigInt("AIX_CAR_DISPLAY_TYPE", type); }
    int getCarDisplayType() { return readConfigInt("AIX_CAR_DISPLAY_TYPE"); }

    // 객체 탐지 민감도 (0: Ultra, 1: High, 2: Middle, 3: Low)
    void setPersonSensitivity(int level) { writeConfigInt("AIX_PERSON_SENSITIVITY", level); }
    int getPersonSensitivity() { return readConfigInt("AIX_PERSON_SENSITIVITY"); }
    
    void setBicycleSensitivity(int level) { writeConfigInt("AIX_BICYCLE_SENSITIVITY", level); }
    int getBicycleSensitivity() { return readConfigInt("AIX_BICYCLE_SENSITIVITY"); }
    
    void setCarSensitivity(int level) { writeConfigInt("AIX_CAR_SENSITIVITY", level); }
    int getCarSensitivity() { return readConfigInt("AIX_CAR_SENSITIVITY"); }

    // 배제 영역 (regionIndex: 0 ~ 7)
    void setExcludeRegionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludeRegionEnable(int regionIndex) { return readConfigBool("AIX_EXCLUDE_REGION_ENABLE" + std::to_string(regionIndex)); }

    // 배제 영역 화면 표시
    void setExcludeRegionDisplayEnable(int regionIndex, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludeRegionDisplayEnable(int regionIndex) { return readConfigBool("AIX_EXCLUDE_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex)); }

    // 배제 영역 표시 (0: Region, 1: Spot)
    void setExcludeRegionType(int regionIndex, int type) { writeConfigInt("AIX_EXCLUDE_REGION_TYPE" + std::to_string(regionIndex), type); }
    int getExcludeRegionType(int regionIndex) { return readConfigInt("AIX_EXCLUDE_REGION_TYPE" + std::to_string(regionIndex)); }

    // 특정 객체 배제
    void setExcludePersonEnable(int regionIndex, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_PERSON_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludePersonEnable(int regionIndex) { return readConfigBool("AIX_EXCLUDE_REGION_PERSON_ENABLE" + std::to_string(regionIndex)); }
    
    void setExcludeBicycleEnable(int regionIndex, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_BICYCLE_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludeBicycleEnable(int regionIndex) { return readConfigBool("AIX_EXCLUDE_REGION_BICYCLE_ENABLE" + std::to_string(regionIndex)); }
    
    void setExcludeCarEnable(int regionIndex, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_CAR_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludeCarEnable(int regionIndex) { return readConfigBool("AIX_EXCLUDE_REGION_CAR_ENABLE" + std::to_string(regionIndex)); }
        
    // 배제 영역 좌표 개수
    void setExcludeRegionPositionCount(int positionCount) { writeConfigInt("AIX_EXCLUDE_REGION_CAPACITY", positionCount); }
    int getExcludeRegionPositionCount() { return readConfigInt("AIX_EXCLUDE_REGION_CAPACITY"); }
    
    // 영역
    void setExcludeRegionPosition(int regionIndex, const std::list<POINT>& points) {
        std::string param;
        for (auto pt : points) {
            param += std::to_string(pt.x) + "," + std::to_string(pt.y) + ",";
        }
        param.pop_back();       // 마지막 , 제거. points가 0개라면 죽는다
        writeConfigString("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex), HttpClient::urlEncode(param));
    }
    std::list<POINT> getExcludeRegionPosition(int regionIndex) {
        std::list<POINT> points;
    
        // URL 인코딩된 좌표 데이터를 읽어서 디코딩
        std::string decodedPositions = HttpClient::urlDecode(readConfigString("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex)));
    
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
    
protected:
    // 설정
    virtual bool readConfig(const std::string& param, std::string& response) const noexcept(false);
    virtual bool writeConfig(const std::string& param, const std::string& value) const noexcept(false);
};

#endif // CAMERA_TRUEN_H
