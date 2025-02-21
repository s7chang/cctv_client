#include "config.h"
#include "rtsp_client.h"
#include "onvif_client.h"
#include "camera_truen.h"
#include "http_exception.h"
#include <thread>
#include <chrono>

void handleMetadata(const std::string& xmlData) {
    // RTP 메타데이터 파싱 및 처리
    std::cout << "Received Metadata: " << xmlData << std::endl;
}

int main() {
    Config& config = Config::getInstance();
    try {
        config.load("../config.ini");
        config.print();
    } catch (const std::runtime_error& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return 1;
    }

    // 설정값을 실제 변수에 저장
    std::string protocol = config.get("CCTV.protocol");
    std::string cctv_ip = config.get("CCTV.cctv_ip");
    int http_port = config.getInt("CCTV.http_port");

    std::string username = config.get("ONVIF.username");
    std::string password = config.get("ONVIF.password");
    int payload_type = config.getInt("ONVIF.metadata_payload_type");
    int reconnect_delay = config.getInt("ONVIF.reconnect_delay");

    curl_global_init(CURL_GLOBAL_ALL);

    // 🔹 1️⃣ 카메라 설정 확인 및 AI 기능 활성화
    CameraTruen camera(cctv_ip, username, password, http_port, protocol);
 
    while (true) {
        try {
            bool detectionEnabled = camera.getObjectDetectionEnable();

            if (!detectionEnabled) {
                std::cout << "[INFO] 객체 탐지가 비활성화되어 있습니다. 활성화 시도 중..." << std::endl;
                camera.setObjectDetectionEnable(true);
            }

            // 켜야 하는 기능들에 대한 체크 필요 (추후에 config.ini에 설정할 수도 있을 듯)

            break; // 성공하면 루프 탈출
        } catch (const HttpException& e) {
            std::cerr << "[WARNING] HTTP 예외 발생 (" << e.getHttpCode() << "): " << e.what() 
                      << " - " << reconnect_delay << "초 후 다시 시도..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(reconnect_delay));

        } catch (const std::exception& e) {
            std::cerr << "[ERROR] 예기치 않은 예외 발생: " << e.what() << std::endl;
            return 1; // 🔹 일반 예외 발생 시 프로그램 종료
        }
    }

    std::cout << std::endl << std::endl << std::endl;
/*
    // 🔹 2️⃣ ONVIFClient를 사용하여 RTSP 메타데이터 스트림 URI 가져오기
    ONVIFClient onvifClient(protocol, cctv_ip + ":" + std::to_string(http_port), username, password);
//    std::string rtsp_url = onvifClient.getMetadataStreamUri();



    // 1️⃣ GetProfiles 호출
    std::string profileToken = onvifClient.getProfileToken();
    if (profileToken.empty()) {
        std::cerr << "Failed to get ProfileToken!" << std::endl;
        return -1;
    }
    std::cout << "Profile Token: " << profileToken << std::endl;

    // 2️⃣ GetStreamUri 호출
    std::string rtspUri = onvifClient.getStreamUri(profileToken);
    if (rtspUri.empty()) {
        std::cerr << "Failed to get RTSP Stream URI!" << std::endl;
        return -1;
    }

    // ✅ 결과 출력
    std::cout << "RTSP Stream URI: " << rtspUri << ", payload_type: " << payload_type << std::endl;
*/
/*


    if (rtsp_url.empty()) {
        std::cerr << "[ERROR] RTSP URI를 가져오지 못했습니다. 종료합니다." << std::endl;
        return 1;
    }

    std::cout << "[INFO] ONVIF RTSP 메타데이터 스트림 URI: " << rtsp_url << std::endl;
*/
    std::string rtsp_url = "rtsp://admin:4321@192.168.52.185:554/video1s1+audio1";

    // 🔹 3️⃣ RTSP 스트림 재연결 루프
    while (true) {
        std::cout << "[INFO] RTSP 메타데이터 스트림 연결 시도 중..." << std::endl;
        RTSPClient rtspClient(rtsp_url, payload_type);
        
        bool connected = rtspClient.startEventStream(handleMetadata);
        if (!connected) {
            std::cout << "[WARNING] 연결이 끊어졌습니다. " << reconnect_delay << "초 후 다시 시도합니다..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(reconnect_delay));
        }
    }

    curl_global_cleanup();

    return 0;
}
