#ifndef RTSP_CLIENT_H
#define RTSP_CLIENT_H

#include <iostream>
#include <string>
#include <functional>

// FFmpeg은 C 라이브러리이므로 C++에서 사용하려면 extern "C"가 필요함
extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
    #include <libswscale/swscale.h>
}

class RTSPClient {
public:
    RTSPClient(const std::string& rtspUrl);
    ~RTSPClient();

    bool startStream(std::function<void(const std::string&)> onMetadataReceived);

private:
    std::string rtspUrl;
    AVFormatContext* formatContext;

    void processPacket(AVPacket* packet, std::function<void(const std::string&)> onMetadataReceived);
};

#endif // RTSP_CLIENT_H
