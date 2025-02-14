#ifndef RTSP_CLIENT_H
#define RTSP_CLIENT_H

#include <string>
#include <functional>
#include <memory>
#include <iostream>
#include <vector>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

class RTSPClient {
public:
    explicit RTSPClient(const std::string& rtspUrl, int payloadType = 107);
    ~RTSPClient();

    bool startEventStream(std::function<void(const std::string&)> onMetadataReceived);

    void setPayloadType(int payloadType);
    int getPayloadType() const;

private:
    std::string rtspUrl;
    AVFormatContext* formatContext;
    int metadataPayloadType;

    int findMetadataStreamIndex();
    bool isMetadataPacket(AVPacket* packet);
    void processMetadataPacket(AVPacket* packet, std::function<void(const std::string&)> onMetadataReceived);
};

#endif // RTSP_CLIENT_H
