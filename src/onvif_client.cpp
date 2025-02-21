#include "onvif_client.h"
#include <curl/curl.h>
#include <iostream>
#include <regex>

// static size_t callback(void* contents, size_t size, size_t nmemb, void* userp) {
//     size_t totalSize = size * nmemb;
//     static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
//     return totalSize;
// }

ONVIFClient::ONVIFClient(const std::string& protocol, const std::string& addr, const std::string& username, const std::string& password)
    : protocol(protocol), addr(addr), username(username), password(password) {}
/*
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

// 🔹 응답 데이터를 저장할 콜백 함수
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// 🔹 SOAP 요청을 보내는 함수 (Digest Authentication 포함)
std::string ONVIFClient::sendSoapRequest(const std::string& url, const std::string& soapRequest, const std::string& action) {
    CURL* curl = curl_easy_init();
    if (!curl) return "";

    std::string response;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/soap+xml");
    std::string soapActionHeader = "SOAPAction: \"" + action + "\"";
    headers = curl_slist_append(headers, soapActionHeader.c_str());

    // 🔹 수동으로 Digest 인증 헤더 추가
    if (!username.empty() && !password.empty()) {
        std::string authHeader = "Authorization: Digest username=\"" + username + "\", password=\"" + password + "\"";
        headers = curl_slist_append(headers, authHeader.c_str());
    }
    // // 🔹 Digest Authentication 적용 (ONVIF는 반드시 Digest 방식 사용)
    // curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
    // curl_easy_setopt(curl, CURLOPT_USERPWD, (username + ":" + password).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soapRequest.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, soapRequest.size());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "SOAP Request Failed: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    return response;
}

// ✅ 1️⃣ GetProfiles 호출 → ProfileToken 획득
std::string  ONVIFClient::getProfileToken() {
    std::string url = "http://" + addr + "/onvif/media";

    std::string soapRequest =
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
        "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">"
        "<s:Body>"
        "<GetProfiles xmlns=\"http://www.onvif.org/ver10/media/wsdl\"/>"
        "</s:Body>"
        "</s:Envelope>";

    std::string response = sendSoapRequest(url, soapRequest, "http://www.onvif.org/ver10/media/wsdl/GetProfiles");

    // 🔹 ProfileToken 추출 (정규 표현식 사용)
    std::regex tokenRegex(R"(Profiles\s+token=\"([^\"]+)\")");
    std::smatch match;
    if (std::regex_search(response, match, tokenRegex)) {
        return match[1].str();
    } else {
        std::cerr << "Error: Could not extract ProfileToken from response!" << std::endl;
        return "";
    }
}

// ✅ 2️⃣ GetStreamUri 호출 → RTSP 스트림 URI 획득
std::string  ONVIFClient::getStreamUri(const std::string& profileToken) {
    std::string url = "http://" + addr + "/onvif/media";

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
        "<ProfileToken>" + profileToken + "</ProfileToken>"
        "</GetStreamUri>"
        "</s:Body>"
        "</s:Envelope>";

    std::string response = sendSoapRequest(url, soapRequest, "http://www.onvif.org/ver10/media/wsdl/GetStreamUri");

    // 🔹 RTSP URI 추출
    std::regex uriRegex(R"(<Uri>(.*?)</Uri>)");
    std::smatch match;
    if (std::regex_search(response, match, uriRegex)) {
        return match[1].str();
    } else {
        std::cerr << "Error: Could not extract RTSP URI from response!" << std::endl;
        return "";
    }
}

/*
// ✅ 3️⃣ 전체 실행 (프로필 가져오고 → RTSP 스트림 URL 가져오기)
int main() {
    std::string ip = "192.168.1.100";  // ONVIF 카메라 IP
    std::string username = "admin";    // ONVIF 계정
    std::string password = "password"; // ONVIF 비밀번호

    // 1️⃣ GetProfiles 호출
    std::string profileToken = getProfileToken(ip, username, password);
    if (profileToken.empty()) {
        std::cerr << "Failed to get ProfileToken!" << std::endl;
        return -1;
    }
    std::cout << "Profile Token: " << profileToken << std::endl;

    // 2️⃣ GetStreamUri 호출
    std::string rtspUri = getStreamUri(ip, username, password, profileToken);
    if (rtspUri.empty()) {
        std::cerr << "Failed to get RTSP Stream URI!" << std::endl;
        return -1;
    }

    // ✅ 결과 출력
    std::cout << "RTSP Stream URI: " << rtspUri << std::endl;
    return 0;
}
*/