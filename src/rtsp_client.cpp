#include "rtsp_client.h"

// 생성자: FFmpeg 네트워크 초기화 및 payloadType 설정
RTSPClient::RTSPClient(const std::string& rtspUrl, int payloadType) 
    : rtspUrl(rtspUrl), formatContext(nullptr), metadataPayloadType(payloadType) {
    avformat_network_init();
}

// 소멸자: FFmpeg 스트림 및 네트워크 해제
RTSPClient::~RTSPClient() {
    if (formatContext) {
        avformat_close_input(&formatContext);
    }
    avformat_network_deinit();
}

// RTP Payload Type 설정
void RTSPClient::setPayloadType(int payloadType) {
    metadataPayloadType = payloadType;
}

// RTP Payload Type 조회
int RTSPClient::getPayloadType() const {
    return metadataPayloadType;
}

// RTSP 이벤트 스트림 시작
bool RTSPClient::startEventStream(std::function<void(const std::string&)> onMetadataReceived) {
    if (avformat_open_input(&formatContext, rtspUrl.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Failed to open RTSP stream" << std::endl;
        return false;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Failed to retrieve stream info" << std::endl;
        return false;
    }

    int metadataStreamIndex = findMetadataStreamIndex();
    if (metadataStreamIndex == -1) {
        std::cerr << "No metadata stream found" << std::endl;
        return false;
    }

    AVPacket packet;
    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == metadataStreamIndex && isMetadataPacket(&packet)) {
            processMetadataPacket(&packet, onMetadataReceived);
        }
        av_packet_unref(&packet);
    }

    return false;
}

// 메타데이터 스트림 인덱스를 찾는 함수
int RTSPClient::findMetadataStreamIndex() {
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        AVStream* stream = formatContext->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_DATA) {
            return i;
        }
    }
    return -1;  // 메타데이터 스트림 없음
}

// RTP 패킷이 메타데이터인지 확인
bool RTSPClient::isMetadataPacket(AVPacket* packet) {
    AVStream* stream = formatContext->streams[packet->stream_index];

    // RTP Payload Type이 설정된 값과 일치하는지 확인
    if (stream->codecpar->codec_id == AV_CODEC_ID_NONE && stream->id == metadataPayloadType) {
        return true;
    }

    return false;
}

// 메타데이터 RTP 패킷 처리
void RTSPClient::processMetadataPacket(AVPacket* packet, std::function<void(const std::string&)> onMetadataReceived) {
    std::string xmlData(reinterpret_cast<char*>(packet->data), packet->size);
    if (xmlData.find("<tt:MetadataStream>") != std::string::npos) { 
        onMetadataReceived(xmlData);
    }
}
