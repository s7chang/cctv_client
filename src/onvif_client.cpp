#include "onvif_client.h"
#include <curl/curl.h>
#include <iostream>
#include <regex>

static size_t callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

ONVIFClient::ONVIFClient(const std::string& protocol, const std::string& addr, const std::string& username, const std::string& password)
    : protocol(protocol), addr(addr), username(username), password(password) {}

std::string ONVIFClient::getMetadataStreamUri() {
    CURL* curl = curl_easy_init();
    if (!curl) return "";

    std::string url = protocol + "://" + addr + "/onvif/media";
    std::string response;
    
    std::string soapRequest =
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
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
        "</s:Envelope>\r\n";  // 🔹 일부 서버는 \r\n 필요

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/soap+xml");
    headers = curl_slist_append(headers, "SOAPAction: \"http://www.onvif.org/ver10/media/wsdl/GetStreamUri\"");

    // 🔹 수동으로 Digest 인증 헤더 추가
    if (!username.empty() && !password.empty()) {
        std::string authHeader = "Authorization: Digest username=\"" + username + "\", password=\"" + password + "\"";
        headers = curl_slist_append(headers, authHeader.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soapRequest.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, soapRequest.size());

    // 🔹 POST 리디렉션 허용 (인증 후 POST 데이터 유지)
    curl_easy_setopt(curl, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);

    // 🔹 User-Agent 설정 (일부 ONVIF 서버는 필요)
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "ONVIF-Client/1.0");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    if (protocol == "https") {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    
    long httpCode = 0;
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

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
/*
std::string ONVIFClient::getMetadataStreamUri() {
    CURL* curl = curl_easy_init();
    if (!curl) return "";

    std::string url = protocol + "://" + addr + "/onvif/media";
    std::string response;
    
    // 🔹 SOAP 요청 (ONVIF 표준)
    std::string soapRequest =
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
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
    headers = curl_slist_append(headers, "SOAPAction: \"http://www.onvif.org/ver10/media/wsdl/GetStreamUri\"");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "post");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soapRequest.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, soapRequest.size());

    // 🔹 User-Agent 설정 (일부 ONVIF 서버는 필요)
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "ONVIF-Client/1.0");

    // // 🔹 Digest Authentication 사용
    // if (!username.empty() && !password.empty()) {
    //     std::string userpwd = username + ":" + password;
    //     curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
    //     curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());
    // }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    if (protocol == "https") {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    
    long httpCode = 0;
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

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
*/