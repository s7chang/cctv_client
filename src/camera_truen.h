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
    void setObjectDetectionEnable(bool enable) { writeConfigBool("AIX_OBJECT_DETECTION_ENABLE", enable); }
    bool getObjectDetectionEnable() { return readConfigBool("AIX_OBJECT_DETECTION_ENABLE"); }

    // 특정 객체 탐지 (PERSON, BICYCLE, CAR)
    void setDetectionXEnable(E_Object objectType, bool enable) { writeConfigBool("AIX_"+ to_string(objectType) + "_DETECTION_ENABLE", enable); }
    bool getDetectionXEnable(E_Object objectType) { return readConfigBool("AIX_" + to_string(objectType) + "_DETECTION_ENABLE"); }

    // 객체 디스플레이 방식 (PERSON, BICYCLE, CAR), (0: off, 1: Bounding Box, 2: Blur)
    void setXDisplayType(E_Object objectType, int type) { writeConfigInt("AIX_" + to_string(objectType) + "_DISPLAY_TYPE", type); }
    int getXDisplayType(E_Object objectType) { return readConfigInt("AIX_" + to_string(objectType) + "_DISPLAY_TYPE"); }
    
    // 객체 탐지 민감도 (PERSON, BICYCLE, CAR), (0: Ultra, 1: High, 2: Middle, 3: Low)
    void setXSensitivity(E_Object objectType, int level) { writeConfigInt("AIX_" + to_string(objectType) + "_SENSITIVITY", level); }
    int getXSensitivity(E_Object objectType) { return readConfigInt("AIX_" + to_string(objectType) + "_SENSITIVITY"); }

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
    void setExcludeRegionXEnable(int regionIndex, E_Object objectType, bool enable) { writeConfigBool("AIX_EXCLUDE_REGION_" + to_string(objectType) + "_ENABLE" + std::to_string(regionIndex), enable); }
    bool getExcludeRegionXEnable(int regionIndex, E_Object objectType) { return readConfigBool("AIX_EXCLUDE_REGION_" + to_string(objectType) + "_ENABLE" + std::to_string(regionIndex)); }
        
    // 배제 영역 Region을 구성하는 점의 최대 개수 (4 ~ 8)
    void setExcludeRegionCapacity(int pointCount) { writeConfigInt("AIX_EXCLUDE_REGION_CAPACITY", pointCount); }
    int getExcludeRegionCapacity() { return readConfigInt("AIX_EXCLUDE_REGION_CAPACITY"); }
    
    // 영역
    void setExcludeRegionPosition(int regionIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getExcludeRegionPosition(int regionIndex) { return readConfigPoints("AIX_EXCLUDE_REGION_POSITION" + std::to_string(regionIndex)); }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.2 스마트 샷 (Smart Shot)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 스마트 샷 활성화
    void setXSmartObjectEnable(E_Object objectType, bool enable) { writeConfigBool("AIX_" + to_string(objectType) + "_SMARTOBJECT_ENABLE", enable); }
    bool getXSmartObjectEnable(E_Object objectType) { return readConfigBool("AIX_" + to_string(objectType) + "_SMARTOBJECT_ENABLE"); }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.3 ANPR (자동차 번호판 인식)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // ANPR 기능 활성화
    void setAnprEnable(bool enable) { writeConfigBool("AIX_ANPR_ENABLE", enable); }
    bool getAnprEnable() { return readConfigBool("AIX_ANPR_ENABLE"); }

    // Display Image OSD 설정
    void setAnprImageOsdDisplayEnable(bool enable) { writeConfigBool("AIX_ANPR_IMAGEOSD_DISPLAY_ENABLE", enable); }
    bool getAnprImageOsdDisplayEnable() { return readConfigBool("AIX_ANPR_IMAGEOSD_DISPLAY_ENABLE"); }

    // Display Image OSD의 출력 스트림 (0: Primary, 1: Secondary#1, 2: Secondary#2, 3: Secondary#3)
    void setAnprImageOsdDisplayStream(int stream) { writeConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_STREAM", stream); }
    int getAnprImageOsdDisplayStream() { return readConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_STREAM"); }

    // Display Image OSD의 Image Type (1: 번호판, 2: 자동차)
    void setAnprImageOsdImageType(int type) { writeConfigInt("AIX_ANPR_IMAGEOSD_IMAGE_TYPE", type); }
    int getAnprImageOsdImageType() { return readConfigInt("AIX_ANPR_IMAGEOSD_IMAGE_TYPE"); }

    // Display Image OSD의 디스플레이 되는 이미지 개수 (1 ~ 4)
    void setAnprImageOsdDisplayNum(int num) { writeConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_NUM", num); }
    int getAnprImageOsdDisplayNum() { return readConfigInt("AIX_ANPR_IMAGEOSD_DISPLAY_NUM"); }

    // Display Image OSD의 위치 좌표 (직사각형 왼쪽-위, 오른쪽-아래 좌표)
    void setAnprImageOsdPosition(const std::list<POINT>& points) { writeConfigPoints("AIX_ANPR_IMAGEOSD_POSITION", points); }
    std::list<POINT> getAnprImageOsdPosition() { return readConfigPoints("AIX_ANPR_IMAGEOSD_POSITION"); }

    // 화면에 표시할 OSD 문자열 앞에 이벤트 타입 표출 기능 사용 여부
    void setAnprOsdDisplayEventType(bool enable) { writeConfigBool("AIX_ANPR_OSD_DISPLAY_EVENT_TYPE", enable); }
    bool getAnprOsdDisplayEventType() { return readConfigBool("AIX_ANPR_OSD_DISPLAY_EVENT_TYPE"); }

    // 화면에 표시할 문자열 (LPR 입력 시 번화판 문자열 정보 그대로 출력)
    void setAnprOsdString(const std::string& text) { writeConfigString("AIX_ANPR_OSD_STRING", text); }
    std::string getAnprOsdString() { return readConfigString("AIX_ANPR_OSD_STRING"); }

    // OSD X좌표 (0 ~ 1000)
    void setAnprOsdX(int x) { writeConfigInt("AIX_ANPR_OSD_X", x); }
    int getAnprOsdX() { return readConfigInt("AIX_ANPR_OSD_X"); }

    // OSD Y좌표 (0 ~ 1000)
    void setAnprOsdY(int y) { writeConfigInt("AIX_ANPR_OSD_Y", y); }
    int getAnprOsdY() { return readConfigInt("AIX_ANPR_OSD_Y"); }

    // 폰트 크기 (12 ~ 84)
    void setAnprOsdFontSize(int size) { writeConfigInt("AIX_ANPR_OSD_FONTSIZE", size); }
    int getAnprOsdFontSize() { return readConfigInt("AIX_ANPR_OSD_FONTSIZE"); }

    // 폰트 색상 (0: White, 1: Gray1, 2: Gray2, 3: Gray3, 4: Black, 5: Red, 6: Green, 7: Blue, 8: Yellow, 9: Orange)
    void setAnprOsdFontColor(int color) { writeConfigInt("AIX_ANPR_OSD_FONTCOLOR", color); }
    int getAnprOsdFontColor() { return readConfigInt("AIX_ANPR_OSD_FONTCOLOR"); }

    // OSD 유지 시간 (1, 5, 10, 30, 60)
    void setAnprOsdDisplayTime(int time) { writeConfigInt("AIX_ANPR_OSD_DISPLAY_TIME", time); }
    int getAnprOsdDisplayTime() { return readConfigInt("AIX_ANPR_OSD_DISPLAY_TIME"); }

    // Event Handler 설정 (action: ALARM, EMAIL, FTP, PRESET, HTTPACTION)
    void setAnprEventActionEnable(E_EventAction action, bool enable) { writeConfigBool("AIX_ANPR_EVENT_ACTION_" + to_string(action) + "_ENABLE", enable); }
    bool getAnprEventActionEnable(E_EventAction action) { return readConfigBool("AIX_ANPR_EVENT_ACTION_" + to_string(action) + "_ENABLE"); }

    // 이벤트 발생 시, 적용할 Preset 번호 (1 ~ 500), HTTP Action 번호 (0: HTTP Action 1, 1: HTTP Action 2: HTTP Action 3, 3: HTTP Action 4)
    void setAnprEventActionNum(E_EventAction action, int num) { writeConfigInt("AIX_ANPR_EVENT_ACTION_" + to_string(action) + "_NUM", num); }
    int getAnprEventActionNum(E_EventAction action) { return readConfigInt("AIX_ANPR_EVENT_ACTION_" + to_string(action) + "_NUM"); }

    // 요일별 이벤트 스케쥴 설정. schedule: 24bit 플래그 값 (예시: 10100111111111111111111111111111 0시~1시:이벤트발생On, 1시~2시:Off, 2시~3시:On, 3시~5시:Off, 5~24시:On)
    void setAnprEventSchedule(E_WeekDay weekDay, const std::string& schedule) { writeConfigString("AIX_ANPR_EVENT_SCHE" + to_string(weekDay), schedule); }
    std::string getAnprEventSchedule(E_WeekDay weekDay) { return readConfigString("AIX_ANPR_EVENT_SCHE" + to_string(weekDay)); }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.4 행동 분석
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 특정 Region 내 이벤트 활성화 (regionIndex: 0 ~ 8, 기본 영역이 존재하는 경우 8을 사용할 수 있음)
    void setRegionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getRegionEnable(int regionIndex) { return readConfigBool("AIX_REGION_ENABLE" + std::to_string(regionIndex)); }

    // Region 디스플레이 활성화
    void setRegionDisplayEnable(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex), enable); }
    bool getRegionDisplayEnable(int regionIndex) { return readConfigBool("AIX_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex)); }

    // Region을 구성하는 점의 최대 개수 (4 ~ 8)
    void setRegionCapacity(int pointCount) { writeConfigInt("AIX_REGION_CAPACITY", pointCount); }
    int getRegionCapacity() { return readConfigInt("AIX_REGION_CAPACITY"); }

    // Region 좌표 설정
    void setRegionPosition(int regionIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_REGION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getRegionPosition(int regionIndex) { return readConfigPoints("AIX_REGION_POSITION" + std::to_string(regionIndex)); }

    // Direction 사용 여부
    void setRegionDirectionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_REGION_DIRECTION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getRegionDirectionEnable(int regionIndex) { return readConfigBool("AIX_REGION_DIRECTION_ENABLE" + std::to_string(regionIndex)); }

    // Direction 좌표 설정
    void setRegionDirectionPosition(int regionIndex, const std::list<POINT> points) { writeConfigPoints("AIX_REGION_DIRECTION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getRegionDirectionPosition(int regionIndex) { return readConfigPoints("AIX_REGION_DIRECTION_POSITION" + std::to_string(regionIndex)); }

    // 이벤트 활성화: 특정 Region 내 객체 (PERSON, BICYCLE, CAR) 이벤트 활성화 여부 (APPEAR, STAY, DIRECTION, ENTER, EXIT, LOITERING, FALLDOWN, FIGHT)
    // reginonIndex가 8인 경우 default region을 의미
    void setRegionEventXB(int regionIndex, E_Object objectType, E_Behavior behavior, bool enable) { writeConfigBool("AIX_REGION_EVENT_" + to_string(objectType) + "_" + to_string(behavior) + "_" + std::to_string(regionIndex), enable); }
    bool getRegionEventXB(int regionIndex, E_Object objectType, E_Behavior behavior) { return readConfigBool("AIX_REGION_EVENT_" + to_string(objectType) + "_" + to_string(behavior) + "_" + std::to_string(regionIndex)); }

    // 특정 Region 내 Stay, Loitering 시간 설정 (1~600초)
    void setRegionEventBDuration(int regionIndex, E_Behavior behavior, int duration) { writeConfigInt("AIX_REGION_EVENT_" + to_string(behavior) + "DURATION" + std::to_string(regionIndex), duration); }
    int getRegionEventBDuration(int regionIndex, E_Behavior behavior) { return readConfigInt("AIX_REGION_EVENT_" + to_string(behavior) + "DURATION" + std::to_string(regionIndex)); }

    // 이벤트 발생 시, 특정 Region 내 이벤트액션(ALARM, EMAIL, FTP, PRESET, HTTPACTION, EVENTOSD) 활성화 여부 설정
    void setRegionEventActionEnable(int regionIndex, E_EventAction action, bool enable) { writeConfigBool("AIX_REGION_EVENT_ACTION_" + to_string(action) + "_ENABLE" + std::to_string(regionIndex), enable); }
    bool getRegionEventActionEnable(int regionIndex, E_EventAction action) { return readConfigBool("AIX_REGION_EVENT_ACTION_" + to_string(action) + "_ENABLE" + std::to_string(regionIndex)); }

    // 이벤트 발생 시, 특정 Region 내 적용할 Preset (1~500), HTTP Action (0~3: HTTP Action 1~4), Event OSD (1~8) 번호 설정
    void setRegionEventActionNum(int regionIndex, E_EventAction action, int num) { writeConfigInt("AIX_REGION_EVENT_ACTION_" + to_string(action) + "NUM" + std::to_string(regionIndex), num); }
    int getRegionEventActionNum(int regionIndex, E_EventAction action) { return readConfigInt("AIX_REGION_EVENT_ACTION_" + to_string(action) + "NUM" + std::to_string(regionIndex)); }

    // 요일별 이벤트 스케쥴 설정. schedule: 24bit 플래그 값 (예시: 10100111111111111111111111111111 0시~1시:이벤트발생On, 1시~2시:Off, 2시~3시:On, 3시~5시:Off, 5~24시:On)
    void setRegionEventSchedule(int regionIndex, E_WeekDay weekDay, const std::string& schedule) { writeConfigString("AIX_REGION_EVENT_SCHE" + to_string(weekDay) + std::to_string(regionIndex), schedule); }
    std::string getRegionEventSchedule(int regionIndex, E_WeekDay weekDay) { return readConfigString("AIX_REGION_EVENT_SCHE" + to_string(weekDay) + std::to_string(regionIndex)); }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 4.5 Line Counting
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 특정 Line 활성화 (lineIndex: 0 ~ 7)
    void setLineEnable(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_ENABLE" + std::to_string(lineIndex), enable); }
    bool getLineEnable(int lineIndex) { return readConfigBool("AIX_LINE_ENABLE" + std::to_string(lineIndex)); }

    // Line 디스플레이 활성화
    void setLineDisplayEnable(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_DISPLAY_ENABLE" + std::to_string(lineIndex), enable); }
    bool getLineDisplayEnable(int lineIndex) { return readConfigBool("AIX_LINE_DISPLAY_ENABLE" + std::to_string(lineIndex)); }

    // 특정 Line에서 탐지할 객체 활성화 (PERSON, BICYCLE, CAR)
    void setLineXEnable(int lineIndex, E_Object objectType, bool enable) { writeConfigBool("AIX_LINE_" + to_string(objectType) + "_ENABLE" + std::to_string(lineIndex), enable); }
    bool getLineXEnable(int lineIndex, E_Object objectType) { return readConfigBool("AIX_LINE_" + to_string(objectType) + "_ENABLE" + std::to_string(lineIndex)); }

    // Line Counting 기능 활성화
    void setLineCountEnable(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_COUNT_ENABLE" + std::to_string(lineIndex), enable); }
    bool getLineCountEnable(int lineIndex) { return readConfigBool("AIX_LINE_COUNT_ENABLE" + std::to_string(lineIndex)); }

    // Line Counting OSD 디스플레이 활성화
    void setLineCountOsdDisplayEnable(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_COUNTOSD_DISPLAY_ENABLE" + std::to_string(lineIndex), enable); }
    bool getLineCountOsdDisplayEnable(int lineIndex) { return readConfigBool("AIX_LINE_COUNTOSD_DISPLAY_ENABLE" + std::to_string(lineIndex)); }

    // Line의 방향성 사용 여부
    void setLineDirection(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_DIRECTION" + std::to_string(lineIndex), enable); }
    bool getLineDirection(int lineIndex) { return readConfigBool("AIX_LINE_DIRECTION" + std::to_string(lineIndex)); }

    // Line을 구성하는 점의 최대 개수 (최대 8개)
    void setLineCapacity(int pointCount) { writeConfigInt("AIX_LINE_CAPACITY", pointCount); }
    int getLineCapacity() { return readConfigInt("AIX_LINE_CAPACITY"); }

    // Line 좌표 설정
    void setLinePosition(int lineIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_LINE_POSITION" + std::to_string(lineIndex), points); }
    std::list<POINT> getLinePosition(int lineIndex) { return readConfigPoints("AIX_LINE_POSITION" + std::to_string(lineIndex)); }

    // Line OSD 이벤트 타입 표출 여부
    void setLineCountOsdDisplayEventType(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_COUNTOSD_DISPLAY_EVENT_TYPE" + std::to_string(lineIndex), enable); }
    bool getLineCountOsdDisplayEventType(int lineIndex) { return readConfigBool("AIX_LINE_COUNTOSD_DISPLAY_EVENT_TYPE" + std::to_string(lineIndex)); }

    // Line OSD의 문자열 설정 (%L1% ~ %L8% 를 입력 시 Line Counting 값이 출력)
    void setLineCountOsdString(int lineIndex, const std::string& text) { writeConfigString("AIX_LINE_COUNTOSD_STRING" + std::to_string(lineIndex), text); }
    std::string getLineCountOsdString(int lineIndex) { return readConfigString("AIX_LINE_COUNTOSD_STRING" + std::to_string(lineIndex)); }

    // Line OSD X 좌표 설정 (0 ~ 1000)
    void setLineCountOsdX(int lineIndex, int x) { writeConfigInt("AIX_LINE_COUNTOSDX" + std::to_string(lineIndex), x); }
    int getLineCountOsdX(int lineIndex) { return readConfigInt("AIX_LINE_COUNTOSDX" + std::to_string(lineIndex)); }

    // Line OSD Y 좌표 설정 (0 ~ 1000)
    void setLineCountOsdY(int lineIndex, int y) { writeConfigInt("AIX_LINE_COUNTOSDY" + std::to_string(lineIndex), y); }
    int getLineCountOsdY(int lineIndex) { return readConfigInt("AIX_LINE_COUNTOSDY" + std::to_string(lineIndex)); }

    // Line OSD 폰트 크기 설정 (12 ~ 84)
    void setLineCountOsdFontSize(int lineIndex, int size) { writeConfigInt("AIX_LINE_COUNTOSD_FONTSIZE" + std::to_string(lineIndex), size); }
    int getLineCountOsdFontSize(int lineIndex) { return readConfigInt("AIX_LINE_COUNTOSD_FONTSIZE" + std::to_string(lineIndex)); }

    // Line OSD 폰트 색상 설정 (0: White, 1: Gray1, 2: Gray2, 3: Gray3, 4: Black, 5: Red, 6: Green, 7: Blue, 8: Yellow)
    void setLineCountOsdFontColor(int lineIndex, int color) { writeConfigInt("AIX_LINE_COUNTOSD_COLOR" + std::to_string(lineIndex), color); }
    int getLineCountOsdFontColor(int lineIndex) { return readConfigInt("AIX_LINE_COUNTOSD_COLOR" + std::to_string(lineIndex)); }

    // Line OSD 유지 시간 설정 (1, 5, 10, 30, 60 초)
    void setLineCountOsdDisplayTime(int lineIndex, int time) { writeConfigInt("AIX_LINE_COUNTOSD_DISPLAY_TIME" + std::to_string(lineIndex), time); }
    int getLineCountOsdDisplayTime(int lineIndex) { return readConfigInt("AIX_LINE_COUNTOSD_DISPLAY_TIME" + std::to_string(lineIndex)); }

    // Line OSD 항상 표시 여부
    void setLineCountOsdDisplayAlways(int lineIndex, bool enable) { writeConfigBool("AIX_LINE_COUNTOSD_DISPLAY_ALLWAYS" + std::to_string(lineIndex), enable); }
    bool getLineCountOsdDisplayAlways(int lineIndex) { return readConfigBool("AIX_LINE_COUNTOSD_DISPLAY_ALLWAYS" + std::to_string(lineIndex)); }

    // Line Counting 이벤트 발생 시, 이벤트액션 설정 (ALARM, EMAIL, FTP, PRESET, HTTPACTION)
    void setLineEventActionEnable(E_EventAction action, bool enable) { writeConfigBool("AIX_LINE_EVENT_ACTION_" + to_string(action) + "_ENABLE", enable); }
    bool getLineEventActionEnable(E_EventAction action) { return readConfigBool("AIX_LINE_EVENT_ACTION_" + to_string(action) + "_ENABLE"); }

    // Line Counting 이벤트 발생 시, 적용할 Preset(1 ~ 500), HTTP Action (0~3: HTTP Action 1~4) 번호 설정
    void setLineEventActionNum(E_EventAction action, int num) { writeConfigInt("AIX_LINE_EVENT_ACTION_" + to_string(action) + "NUM", num); }
    int getLineEventActionNum(E_EventAction action) { return readConfigInt("AIX_LINE_EVENT_ACTION_" + to_string(action) + "NUM"); }

    // 요일별 이벤트 스케쥴 설정. schedule: 24bit 플래그 값 (예시: 10100111111111111111111111111111 0시~1시:이벤트발생On, 1시~2시:Off, 2시~3시:On, 3시~5시:Off, 5~24시:On)
    void setRegionEventSchedule(E_WeekDay weekDay, const std::string& schedule) { writeConfigString("AIX_LINE_EVENT_SCHE" + to_string(weekDay), schedule); }
    std::string getRegionEventSchedule(E_WeekDay weekDay) { return readConfigString("AIX_LINE_EVENT_SCHE" + to_string(weekDay)); }


    /////////////////////////////////////////////////////////////////////////////////////////////
    // 4.6 속도 감지 (Speed Detection)
    /////////////////////////////////////////////////////////////////////////////////////////////

    // Vehicle Speed Unit 설정 (0: km/h, 1: mi/h)
    void setSpeedUnit(int unit) { writeConfigInt("AIX_SPEEDUNIT", unit); }
    int getSpeedUnit() { return readConfigInt("AIX_SPEEDUNIT"); }

    // 특정 Speed Region 활성화 (regionIndex: 0 ~ 3)
    void setSpeedRegionEnable(int regionIndex, bool enable) { writeConfigBool("AIX_SPEED_REGION_ENABLE" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionEnable(int regionIndex) { return readConfigBool("AIX_SPEED_REGION_ENABLE" + std::to_string(regionIndex)); }

    // Speed Region 디스플레이 활성화
    void setSpeedRegionDisplayEnable(int regionIndex, bool enable) { writeConfigBool("AIX_SPEED_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionDisplayEnable(int regionIndex) { return readConfigBool("AIX_SPEED_REGION_DISPLAY_ENABLE" + std::to_string(regionIndex)); }

    // Speed Region 높이 설정 (1~50m)
    void setSpeedRegionHeight(int regionIndex, int height) { writeConfigInt("AIX_SPEED_REGION_HEIGHT" + std::to_string(regionIndex), height); }
    int getSpeedRegionHeight(int regionIndex) { return readConfigInt("AIX_SPEED_REGION_HEIGHT" + std::to_string(regionIndex)); }

    // Speed Region의 최대 점 개수 (4)
    void setSpeedRegionCapacity(int capacity) { writeConfigInt("AIX_SPEED_REGION_CAPACITY", capacity); }
    int getSpeedRegionCapacity() { return readConfigInt("AIX_SPEED_REGION_CAPACITY"); }

    // Speed Region 좌표 설정
    void setSpeedRegionPosition(int regionIndex, const std::list<POINT>& points) { writeConfigPoints("AIX_SPEED_REGION_POSITION" + std::to_string(regionIndex), points); }
    std::list<POINT> getSpeedRegionPosition(int regionIndex) { return readConfigPoints("AIX_SPEED_REGION_POSITION" + std::to_string(regionIndex)); }

    // OSD 디스플레이 활성화
    void setSpeedRegionOsdDisplayEnable(int regionIndex, bool enable) { writeConfigBool("AIX_SPEED_REGION_OSD_DISPLAY_ENABLE" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionOsdDisplayEnable(int regionIndex) { return readConfigBool("AIX_SPEED_REGION_OSD_DISPLAY_ENABLE" + std::to_string(regionIndex)); }

    // 속도 감지 OSD 문자열 설정
    void setSpeedOsdString(int regionIndex, const std::string& text) { writeConfigString("AIX_SPEED_OSD_STRING" + std::to_string(regionIndex), text); }
    std::string getSpeedOsdString(int regionIndex) { return readConfigString("AIX_SPEED_OSD_STRING" + std::to_string(regionIndex)); }

    // 속도 감지 OSD 위치 설정
    void setSpeedOsdX(int regionIndex, int x) { writeConfigInt("AIX_SPEED_OSD_X" + std::to_string(regionIndex), x); }
    int getSpeedOsdX(int regionIndex) { return readConfigInt("AIX_SPEED_OSD_X" + std::to_string(regionIndex)); }

    void setSpeedOsdY(int regionIndex, int y) { writeConfigInt("AIX_SPEED_OSD_Y" + std::to_string(regionIndex), y); }
    int getSpeedOsdY(int regionIndex) { return readConfigInt("AIX_SPEED_OSD_Y" + std::to_string(regionIndex)); }

    // OSD 글꼴 크기 설정
    void setSpeedOsdFontSize(int regionIndex, int size) { writeConfigInt("AIX_SPEED_OSD_FONTSIZE" + std::to_string(regionIndex), size); }
    int getSpeedOsdFontSize(int regionIndex) { return readConfigInt("AIX_SPEED_OSD_FONTSIZE" + std::to_string(regionIndex)); }

    // OSD 글꼴 색상 설정
    void setSpeedOsdFontColor(int regionIndex, int color) { writeConfigInt("AIX_SPEED_OSD_COLOR" + std::to_string(regionIndex), color); }
    int getSpeedOsdFontColor(int regionIndex) { return readConfigInt("AIX_SPEED_OSD_COLOR" + std::to_string(regionIndex)); }

    // OSD 유지 시간 설정 (1, 5, 10, 30, 60 초)
    void setSpeedOsdDisplayTime(int regionIndex, int time) { writeConfigInt("AIX_SPEED_OSD_DISPLAY_TIME" + std::to_string(regionIndex), time); }
    int getSpeedOsdDisplayTime(int regionIndex) { return readConfigInt("AIX_SPEED_OSD_DISPLAY_TIME" + std::to_string(regionIndex)); }

    // 속도 감지 이벤트 활성화 (Speed Event)
    void setSpeedRegionEventTrigger(int regionIndex, bool enable) { writeConfigBool("AIX_SPEED_REGION_EVENT_TRIGGER" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionEventTrigger(int regionIndex) { return readConfigBool("AIX_SPEED_REGION_EVENT_TRIGGER" + std::to_string(regionIndex)); }

    // 속도 감지 이벤트 핸들러 (ALARM, EMAIL, FTP, PRESET, HTTPACTION)
    void setSpeedRegionEventActionEnable(int regionIndex, E_EventAction action, bool enable) { writeConfigBool("AIX_SPEED_REGION_EVENT_ACTION_" + to_string(action) + "_ENABLE" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionEventActionEnable(int regionIndex, E_EventAction action) { return readConfigBool("AIX_SPEED_REGION_EVENT_ACTION_" + to_string(action) + "_ENABLE" + std::to_string(regionIndex)); }

    // 속도 감지 이벤트 OSD 활성화 여부
    void setSpeedRegionEventOsdEnable(int regionIndex, bool enable) { writeConfigBool("AIX_SPEED_REGION_EVENT_ACTION_EVENTOSD_ENABLE" + std::to_string(regionIndex), enable); }
    bool getSpeedRegionEventOsdEnable(int regionIndex) { return readConfigBool("AIX_SPEED_REGION_EVENT_ACTION_EVENTOSD_ENABLE" + std::to_string(regionIndex)); }

    // 속도 감지 이벤트 적용할 OSD 번호 설정 (1~8)
    void setSpeedRegionEventOsdNum(int regionIndex, int num) { writeConfigInt("AIX_SPEED_REGION_EVENT_ACTION_EVENTOSDNUM" + std::to_string(regionIndex), num); }
    int getSpeedRegionEventOsdNum(int regionIndex) { return readConfigInt("AIX_SPEED_REGION_EVENT_ACTION_EVENTOSDNUM" + std::to_string(regionIndex)); }

    // 속도 감지 이벤트 요일별 스케줄 설정 (24bit 플래그 값)
    void setSpeedRegionEventSchedule(int regionIndex, E_WeekDay weekDay, const std::string& schedule) { writeConfigString("AIX_SPEED_REGION_EVENT_SCHE" + to_string(weekDay) + std::to_string(regionIndex), schedule); }
    std::string getSpeedRegionEventSchedule(int regionIndex, E_WeekDay weekDay) { return readConfigString("AIX_SPEED_REGION_EVENT_SCHE" + to_string(weekDay) + std::to_string(regionIndex)); }


protected:
    // 설정
    virtual bool readConfig(const std::string& param, std::string& response) const noexcept(false);
    virtual bool writeConfig(const std::string& param, const std::string& value) const noexcept(false);
};

#endif // CAMERA_TRUEN_H
