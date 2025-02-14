#ifndef CAMERA_TRUEN_H
#define CAMERA_TRUEN_H

#include "camera.h"

class CameraTruen : public Camera {
public:
    CameraTruen(const std::string& cameraIp, int port = 80, const std::string& protocol = "http") : Camera(cameraIp, port, protocol) {}

    // [1] 객체 탐지 (Object Detection)
    void setObjectDetection(bool enable) { writeConfig("AIX_OBJECT_DETECTION_ENABLE", enable ? "1" : "0"); }
    bool getObjectDetection() { return readConfigBool("AIX_OBJECT_DETECTION_ENABLE"); }
    
    void setPersonDetection(bool enable) { writeConfig("AIX_PERSON_DETECTION_ENABLE", enable ? "1" : "0"); }
    bool getPersonDetection() { return readConfigBool("AIX_PERSON_DETECTION_ENABLE"); }
    
    void setBicycleDetection(bool enable) { writeConfig("AIX_BICYCLE_DETECTION_ENABLE", enable ? "1" : "0"); }
    bool getBicycleDetection() { return readConfigBool("AIX_BICYCLE_DETECTION_ENABLE"); }
    
    void setCarDetection(bool enable) { writeConfig("AIX_CAR_DETECTION_ENABLE", enable ? "1" : "0"); }
    bool getCarDetection() { return readConfigBool("AIX_CAR_DETECTION_ENABLE"); }
    
    

    // [2] 스마트 샷 (Smart Shot)
    // 스마트 샷 전체 활성화/비활성화
    void enableSmartShot(bool enable) { writeConfig("AIX_SMARTSHOT_ENABLE", enable ? "1" : "0"); }
    bool getSmartShotStatus() { return readConfigBool("AIX_SMARTSHOT_ENABLE"); }

    // 개별 객체별 스마트 샷 활성화
    void enablePersonSmartShot(bool enable) { writeConfig("AIX_PERSON_SMARTOBJECT_ENABLE", enable ? "1" : "0"); }
    void enableBicycleSmartShot(bool enable) { writeConfig("AIX_BICYCLE_SMARTOBJECT_ENABLE", enable ? "1" : "0"); }
    void enableCarSmartShot(bool enable) { writeConfig("AIX_CAR_SMARTOBJECT_ENABLE", enable ? "1" : "0"); }

    bool getPersonSmartShotStatus() { return readConfigBool("AIX_PERSON_SMARTOBJECT_ENABLE"); }
    bool getBicycleSmartShotStatus() { return readConfigBool("AIX_BICYCLE_SMARTOBJECT_ENABLE"); }
    bool getCarSmartShotStatus() { return readConfigBool("AIX_CAR_SMARTOBJECT_ENABLE"); }

    // 객체 속성 설정
    std::string getPersonGender() { return readConfigString("AIX_PERSON_GENDER"); }
    void setPersonGender(const std::string& gender) { writeConfig("AIX_PERSON_GENDER", gender); }

    std::string getPersonClothingTopColor() { return readConfigString("AIX_PERSON_TOP_COLOR"); }
    void setPersonClothingTopColor(const std::string& color) { writeConfig("AIX_PERSON_TOP_COLOR", color); }

    std::string getPersonClothingBottomColor() { return readConfigString("AIX_PERSON_BOTTOM_COLOR"); }
    void setPersonClothingBottomColor(const std::string& color) { writeConfig("AIX_PERSON_BOTTOM_COLOR", color); }

    bool isWearingGlasses() { return readConfigBool("AIX_PERSON_ACCESSORY_GLASSES"); }
    void setWearingGlasses(bool enable) { writeConfig("AIX_PERSON_ACCESSORY_GLASSES", enable ? "1" : "0"); }

    bool isWearingMask() { return readConfigBool("AIX_PERSON_ACCESSORY_MASK"); }
    void setWearingMask(bool enable) { writeConfig("AIX_PERSON_ACCESSORY_MASK", enable ? "1" : "0"); }

    bool isWearingHat() { return readConfigBool("AIX_PERSON_ACCESSORY_HAT"); }
    void setWearingHat(bool enable) { writeConfig("AIX_PERSON_ACCESSORY_HAT", enable ? "1" : "0"); }

    bool isWearingHelmet() { return readConfigBool("AIX_PERSON_ACCESSORY_HELMET"); }
    void setWearingHelmet(bool enable) { writeConfig("AIX_PERSON_ACCESSORY_HELMET", enable ? "1" : "0"); }

    std::string getPersonBelongingType() { return readConfigString("AIX_PERSON_BELONGING_TYPE"); }
    void setPersonBelongingType(const std::string& type) { writeConfig("AIX_PERSON_BELONGING_TYPE", type); }

    // 자동차 속성 설정
    std::string getCarType() { return readConfigString("AIX_CAR_TYPE"); }
    void setCarType(const std::string& type) { writeConfig("AIX_CAR_TYPE", type); }

    std::string getCarColor() { return readConfigString("AIX_CAR_COLOR"); }
    void setCarColor(const std::string& color) { writeConfig("AIX_CAR_COLOR", color); }

    // 자전거 속성 설정
    std::string getBicycleType() { return readConfigString("AIX_BICYCLE_TYPE"); }
    void setBicycleType(const std::string& type) { writeConfig("AIX_BICYCLE_TYPE", type); }

    std::string getBicycleColor() { return readConfigString("AIX_BICYCLE_COLOR"); }
    void setBicycleColor(const std::string& color) { writeConfig("AIX_BICYCLE_COLOR", color); }



    // [3] ANPR (Automatic Number Plate Recognition)
    void enableANPR(bool enable) { writeConfig("AIX_ANPR_ENABLE", enable ? "1" : "0"); }
    bool getANPRStatus() { return readConfigBool("AIX_ANPR_ENABLE"); }

    // [4] 행동 분석 (Behavior Analysis)
    void enableBehaviorAnalysis(bool enable) { writeConfig("AIX_REGION_ENABLE0", enable ? "1" : "0"); }
    bool getBehaviorAnalysisStatus() { return readConfigBool("AIX_REGION_ENABLE0"); }

    // [5] Line Counting (라인 카운팅)
    void enableLineCounting(bool enable) { writeConfig("AIX_REGION_ENABLE1", enable ? "1" : "0"); }
    bool getLineCountingStatus() { return readConfigBool("AIX_REGION_ENABLE1"); }

    // [6] Vehicle Speed (자동차 속도 감지)
    void enableVehicleSpeed(bool enable) { writeConfig("AIX_VEHICLE_SPEED_ENABLE", enable ? "1" : "0"); }
    bool getVehicleSpeedStatus() { return readConfigBool("AIX_VEHICLE_SPEED_ENABLE"); }

    // [7] Tampering Detection (카메라 훼손 감지)
    void enableTamperingDetection(bool enable) { writeConfig("AIX_TAMPERING_ENABLE", enable ? "1" : "0"); }
    bool getTamperingDetectionStatus() { return readConfigBool("AIX_TAMPERING_ENABLE"); }

    // [8] Crowd Counting (군집 카운팅)
    void enableCrowdCounting(bool enable) { writeConfig("AIX_CROWD_COUNTING_ENABLE", enable ? "1" : "0"); }
    bool getCrowdCountingStatus() { return readConfigBool("AIX_CROWD_COUNTING_ENABLE"); }

    // [9] Auto Tracking (자동 추적)
    void enableAutoTracking(bool enable) { writeConfig("AIX_AUTO_TRACKING_ENABLE", enable ? "1" : "0"); }
    bool getAutoTrackingStatus() { return readConfigBool("AIX_AUTO_TRACKING_ENABLE"); }
    
protected:
    // 설정
    virtual bool readConfig(const std::string& param, std::string& response) const;
    virtual bool writeConfig(const std::string& param, const std::string& value) const;
};

#endif // CAMERA_TRUEN_H
