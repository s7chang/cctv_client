#ifndef CAMERA_TRUEN_H
#define CAMERA_TRUEN_H

#include "camera.h"

class CameraTruen : public Camera {
public:
    CameraTruen(const std::string& cameraIp, int port = 80, const std::string& protocol = "http") : Camera(cameraIp, port, protocol) {}

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.1 객체 탐지
    /////////////////////////////////////////////////////////////////////////////////////////////////

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
        
    // 배제 영역 Region을 구성하는 점의 최대 개수 (4 ~ 8)
    void setExcludeRegionCapacity(int pointCount) { writeConfigInt("AIX_EXCLUDE_REGION_CAPACITY", pointCount); }
    int getExcludeRegionCapacity() { return readConfigInt("AIX_EXCLUDE_REGION_CAPACITY"); }
    
    // 영역
    void setExcludeRegionPosition(int regionIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getExcludeRegionPosition(int regionIndex) { return readConfigPoints("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex)); }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.2 스마트 샷 (Smart Shot)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 사람 스마트 샷 활성화
    void setPersonSmartShot(bool enable) { writeConfigBool("AIX_PERSON_SMARTOBJECT_ENABLE", enable); }
    bool getPersonSmartShot() { return readConfigBool("AIX_PERSON_SMARTOBJECT_ENABLE"); }

    // 자전거 스마트 샷 활성화
    void setBicycleSmartShot(bool enable) { writeConfigBool("AIX_BICYCLE_SMARTOBJECT_ENABLE", enable); }
    bool getBicycleSmartShot() { return readConfigBool("AIX_BICYCLE_SMARTOBJECT_ENABLE"); }

    // 자동차 스마트 샷 활성화
    void setCarSmartShot(bool enable) { writeConfigBool("AIX_CAR_SMARTOBJECT_ENABLE", enable); }
    bool getCarSmartShot() { return readConfigBool("AIX_CAR_SMARTOBJECT_ENABLE"); }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.3 ANPR (자동차 번호판 인식)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // ANPR 기능 활성화
    void setANPREnable(bool enable) { writeConfigBool("AIX_ANPR_ENABLE", enable); }
    bool getANPREnable() { return readConfigBool("AIX_ANPR_ENABLE"); }

    // Display Image OSD 설정
    void setANPRImageOSDEnable(bool enable) { writeConfigBool("AIX_ANPR_IMAGEOSD_DISPLAY_ENABLE", enable); }
    bool getANPRImageOSDEnable() { return readConfigBool("AIX_ANPR_IMAGEOSD_DISPLAY_ENABLE"); }

    void setANPRImageOSDStream(int stream) { writeConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_STREAM", stream); }
    int getANPRImageOSDStream() { return readConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_STREAM"); }

    void setANPRImageOSDType(int type) { writeConfigInt("AIX_ANPR_IMAGEOSD_IMAGE_TYPE", type); }
    int getANPRImageOSDType() { return readConfigInt("AIX_ANPR_IMAGEOSD_IMAGE_TYPE"); }

    void setANPRImageOSDNum(int num) { writeConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_NUM", num); }
    int getANPRImageOSDNum() { return readConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_NUM"); }

    void setANPRImageOSDPosition(const std::list<POINT>& points) { writeConfigPoints("AIX_ANPR_IMAGEOSD_POSITION", points); }
    std::list<POINT> getANPRImageOSDPosition() { return readConfigPoints("AIX_ANPR_IMAGEOSD_POSITION"); }

    // Display OSD 설정
    void setANPROSDEnable(bool enable) { writeConfigBool("AIX_ANPR_OSD_DISPLAY_EVENT_TYPE", enable); }
    bool getANPROSDEnable() { return readConfigBool("AIX_ANPR_OSD_DISPLAY_EVENT_TYPE"); }

    void setANPROSDString(const std::string& text) { writeConfigString("AIX_ANPR_OSD_STRING", text); }
    std::string getANPROSDString() { return readConfigString("AIX_ANPR_OSD_STRING"); }

    void setANPROSDX(int x) { writeConfigInt("AIX_ANPR_OSD_X", x); }
    int getANPROSDX() { return readConfigInt("AIX_ANPR_OSD_X"); }

    void setANPROSDY(int y) { writeConfigInt("AIX_ANPR_OSD_Y", y); }
    int getANPROSDY() { return readConfigInt("AIX_ANPR_OSD_Y"); }

    void setANPROSDFontSize(int size) { writeConfigInt("AIX_ANPR_OSD_FONTSIZE", size); }
    int getANPROSDFontSize() { return readConfigInt("AIX_ANPR_OSD_FONTSIZE"); }

    void setANPROSDFontColor(int color) { writeConfigInt("AIX_ANPR_OSD_FONTCOLOR", color); }
    int getANPROSDFontColor() { return readConfigInt("AIX_ANPR_OSD_FONTCOLOR"); }

    void setANPROSDDisplayTime(int time) { writeConfigInt("AIX_ANPR_OSD_DISPLAY_TIME", time); }
    int getANPROSDDisplayTime() { return readConfigInt("AIX_ANPR_OSD_DISPLAY_TIME"); }

    // Event Handler 설정
    void setANPREventAlarmEnable(bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_ALARM_ENABLE", enable); }
    bool getANPREventAlarmEnable() { return readConfigBool("AIX_ANPR_EVENT_ACTION_ALARM_ENABLE"); }

    void setANPREventEmailEnable(bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_EMAIL_ENABLE", enable); }
    bool getANPREventEmailEnable() { return readConfigBool("AIX_ANPR_EVENT_ACTION_EMAIL_ENABLE"); }

    void setANPREventFTPEnable(bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_FTP_ENABLE", enable); }
    bool getANPREventFTPEnable() { return readConfigBool("AIX_ANPR_EVENT_ACTION_FTP_ENABLE"); }

    void setANPREventPresetEnable(bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_PRESET_ENABLE", enable); }
    bool getANPREventPresetEnable() { return readConfigBool("AIX_ANPR_EVENT_ACTION_PRESET_ENABLE"); }

    void setANPREventPresetNum(int num) { writeConfigInt("AIX_ANPR_EVENT_ACTION_PRESET_NUM", num); }
    int getANPREventPresetNum() { return readConfigInt("AIX_ANPR_EVENT_ACTION_PRESET_NUM"); }

    void setANPREventHTTPEnable(bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_HTTPACTION_ENABLE", enable); }
    bool getANPREventHTTPEnable() { return readConfigBool("AIX_ANPR_EVENT_ACTION_HTTPACTION_ENABLE"); }

    void setANPREventHTTPActionNum(int num) { writeConfigInt("AIX_ANPR_EVENT_ACTION_HTTPACTIONNUM", num); }
    int getANPREventHTTPActionNum() { return readConfigInt("AIX_ANPR_EVENT_ACTION_HTTPACTIONNUM"); }

    void setANPREventSchedule(E_WeekDay weekDay, const std::string& schedule) { writeConfigString("AIX_ANPR_EVENT_SCHE" + to_string(weekDay), schedule); }
    std::string getANPREventSchedule(E_WeekDay weekDay) { return readConfigString("AIX_ANPR_EVENT_SCHE" + to_string(weekDay)); }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.4 행동 분석 (Behavior Analysis)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 특정 Region 내 이벤트 활성화 (regionIndex: 0 ~ 7)
    void setBehaviorAnalysisRegionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getBehaviorAnalysisRegionEnable(int regionIndex) { return readConfigBool("AIX_REGION_ENABLE" + std::to_string(regionIndex)); }

    // Region 디스플레이 활성화
    void setBehaviorAnalysisRegionDisplay(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex), enable); }
    bool getBehaviorAnalysisRegionDisplay(int regionIndex) { return readConfigBool("AIX_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex)); }

    // Region 을 구성하는 점의 최대 개수 (4 ~ 8)
    void setBehaviorAnalysisRegionCapacity(int pointCount) { writeConfigInt("AIX_REGION_CAPACITY", pointCount); }
    int getBehaviorAnalysisRegionCapacity() { return readConfigInt("AIX_REGION_CAPACITY"); }

    // Region 좌표 설정
    void setBehaviorAnalysisRegionPosition(int regionIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_REGION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getBehaviorAnalysisRegionPosition(int regionIndex) { return readConfigPoints("AIX_REGION_POSITION" + std::to_string(regionIndex)); }

    // Direction 사용 여부
    void setBehaviorDirectionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_DIRECTION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getBehaviorDirectionEnable(int regionIndex) { return readConfigBool("AIX_REGION_DIRECTION_ENABLE" + std::to_string(regionIndex)); }

    // Direction 좌표 설정
    void setBehaviorDirectionPosition(int regionIndex, const std::list<POINT> points) { writeConfigPoints("AIX_REGION_DIRECTION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getBehaviorDirectionPosition(int regionIndex) { return readConfigPoints("AIX_REGION_DIRECTION_POSITION" + std::to_string(regionIndex)); }

    // 이벤트 활성화: 특정 Region 내 객체 (PERSON, BICYCLE, CAR) 이벤트 활성화 여부 (APPEAR, STAY, DIRECTION, ENTER, EXIT, LOITERING, FALLDOWN, FIGHT)
    // reginonIndex가 8인 경우 default region을 의미
    void setBehaviorEvent(int regionIndex, E_Object objectType, E_Behavior behavior, bool enable) { writeConfigBool("AIX_REGION_EVENT_" + to_string(objectType) + "_" + to_string(behavior) + "_" + std::to_string(regionIndex), enable); }
    bool getBehaviorEvent(int regionIndex, E_Object objectType, E_Behavior behavior) { return readConfigBool("AIX_REGION_EVENT_PERSON_" + to_string(objectType) + "_" + to_string(behavior) + "_" + std::to_string(regionIndex)); }

protected:
    // 설정
    virtual bool readConfig(const std::string& param, std::string& response) const noexcept(false);
    virtual bool writeConfig(const std::string& param, const std::string& value) const noexcept(false);
};

#endif // CAMERA_TRUEN_H
