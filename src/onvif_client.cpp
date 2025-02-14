#include "onvif_client.h"
#include <curl/curl.h>
#include <iostream>
#include <regex>

ONVIFClient::ONVIFClient(const std::string& protocol, const std::string& addr, const std::string& username, const std::string& password)
    : protocol(protocol), addr(addr), username(username), password(password) {}

std::string ONVIFClient::getMetadataStreamUri() {
    CURL* curl = curl_easy_init();
    if (!curl) return "";

    std::string url = protocol + "://" + addr + "/onvif/media";
    std::string response;
    std::string soapRequest =
        "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">"
        "<s:Body>"
        "<GetStreamUri xmlns=\"http://www.onvif.org/ver10/media/wsdl\">"
        "<StreamSetup>"
        "<Stream xmlns=\"http://www.onvif.org/ver10/schema\">RTP-Unicast</Stream>"
        "<Transport xmlns=\"http://www.onvif.org/ver10/schema\">"
        "<Protocol>RTSP</Protocol>"
        "</Transport>"
        "</StreamSetup>"
        "<ProfileToken>MetadataProfile</ProfileToken>"
        "</GetStreamUri>"
        "</s:Body>"
        "</s:Envelope>";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/soap+xml");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soapRequest.c_str());
    curl_easy_setopt(curl, CURLOPT_USERPWD, (username + ":" + password).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) -> size_t {
        size_t totalSize = size * nmemb;
        static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    // 🔹 HTTPS 지원: SSL 인증서 검증 설정
    if (protocol == "https") {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // 서버 인증서 검증 비활성화 (보안상 위험할 수 있음)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // 호스트 검증 비활성화
    }

    CURLcode res = curl_easy_perform(curl);
    
    long httpCode = 0;
    if (res == CURLE_OK) {
        // 🔹 HTTP 응답 코드 확인
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    // 🔹 200 OK가 아닌 경우 실패 처리
    if (res != CURLE_OK || httpCode != 200) {
        std::cerr << "HTTP Request Failed! Status Code: " << httpCode 
                  << ", CURL Error: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    // 🔹 RTSP URI 추출
    std::regex rtspRegex("<tt:Uri>(.*?)</tt:Uri>");
    std::smatch match;
    if (std::regex_search(response, match, rtspRegex)) {
        return match[1].str();
    }

    return "";
}
