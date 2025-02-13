#include "rtsp_client.h"

RTSPClient::RTSPClient(const std::string& rtspUrl) : rtspUrl(rtspUrl), formatContext(nullptr) {
    // FFmpeg 네트워크 초기화
    avformat_network_init();
}

RTSPClient::~RTSPClient() {
    if (formatContext) {
        avformat_close_input(&formatContext);
    }
    // FFmpeg 네트워크 해제
    avformat_network_deinit();
}

bool RTSPClient::startStream(std::function<void(const std::string&)> onMetadataReceived) {
    // FFmpeg 컨텍스트 초기화
    if (avformat_open_input(&formatContext, rtspUrl.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Failed to open RTSP stream" << std::endl;
        return false;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Failed to retrieve stream info" << std::endl;
        return false;
    }

    AVPacket packet;
    while (av_read_frame(formatContext, &packet) >= 0) {
        processPacket(&packet, onMetadataReceived);
        av_packet_unref(&packet);
    }

    return false;
}

void RTSPClient::processPacket(AVPacket* packet, std::function<void(const std::string&)> onMetadataReceived) {
    std::string xmlData(reinterpret_cast<char*>(packet->data), packet->size);
    onMetadataReceived(xmlData);
}
