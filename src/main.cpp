#include "config.h"
#include "rtsp_client.h"
#include "http_client.h"
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
	std::string cctv_ip         = config.get("CCTV.cctv_ip");
	std::string rtsp_url        = config.get("CCTV.rtsp_url");
	std::string http_api_url    = config.get("CCTV.http_api_url");
	int reconnect_delay         = config.getInt("RTSP.reconnect_delay");
	std::string enable_ai_cmd   = config.get("HTTP_COMMANDS.enable_ai");
    std::string ai_status_url   = http_api_url + "?action=readparam&" + config.get("HTTP_COMMANDS.check_ai_status");

    // AI 상태 확인 후 필요하면 활성화
    if (!HTTPClient::checkAIStatus(ai_status_url)) {
        std::cout << "AI is disabled. Enabling AI..." << std::endl;
        HTTPClient::sendCommand(http_api_url, enable_ai_cmd);
    }

    // RTSP 스트림 재연결 루프
    while (true) {
        std::cout << "Connecting to RTSP stream..." << std::endl;
        RTSPClient rtspClient(rtsp_url);
        
        bool connected = rtspClient.startStream(handleMetadata);
        if (!connected) {
            std::cout << "Connection lost. Retrying in " << reconnect_delay << " seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(reconnect_delay));
        }
    }

    return 0;
}
