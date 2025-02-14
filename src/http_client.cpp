#include "http_client.h"
#include <iostream>
#include <curl/curl.h>

bool HttpClient::sendRequest(const std::string& protocol, const std::string& method, const std::string& url, std::string* response) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

    if (response) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) -> size_t {
            size_t totalSize = size * nmemb;
            static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
            return totalSize;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    }
    else {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    }

    // 🔹 HTTPS 지원: SSL 옵션 추가
    if (protocol == "https") {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // 서버 인증서 검증 비활성화 (보안상 위험할 수 있음)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // 호스트 검증 비활성화
    }

    CURLcode res = curl_easy_perform(curl);

    long httpCode = 0;
    if (res == CURLE_OK) {
        // 🔹 HTTP 응답 상태 코드 확인
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }

    curl_easy_cleanup(curl);

    // 🔹 200 OK 검사
    return (res == CURLE_OK && httpCode == 200);
}
