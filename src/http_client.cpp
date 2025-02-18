#include <iostream>
#include <curl/curl.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

#include "http_client.h"
#include "http_exception.h"

static size_t callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

bool HttpClient::sendRequest(const std::string& protocol, const std::string& method, const std::string& url, const std::string& username, const std::string& passwd, std::string* response) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("CURL 초기화 실패");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

    // 🔹 ONVIF는 Digest Authentication을 요구하므로 설정
    if (!username.empty() && !passwd.empty()) {
        std::string userpwd = username + ":" + passwd;
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
        curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());
    }

    if (response) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    } else {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    }

    // 🔹 HTTPS 지원: SSL 옵션 추가
    if (protocol == "https") {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // 서버 인증서 검증 비활성화
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // 호스트 검증 비활성화
    }

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // 🔹 디버깅을 위해 상세 로그 출력

    CURLcode res = curl_easy_perform(curl);

    long httpCode = 0;
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }

    curl_easy_cleanup(curl);

    // 🔹 CURL 오류 발생 시 예외 처리
    if (res != CURLE_OK) {
        throw std::runtime_error("CURL 요청 실패: " + std::string(curl_easy_strerror(res)));
    }

    // 🔹 HTTP 상태 코드별 예외 처리
    switch (httpCode) {
        case 200:
            break;

        case 400:
            throw HttpException("400 Bad Request: 잘못된 요청", httpCode);

        case 401:
            throw HttpException("401 Unauthorized: 인증 실패", httpCode);

        case 403:
            throw HttpException("403 Forbidden: 접근 권한 없음", httpCode);

        case 404:
            throw HttpException("404 Not Found: 요청한 리소스를 찾을 수 없음", httpCode);

        case 500:
            throw HttpException("500 Internal Server Error: 서버 내부 오류", httpCode);

        case 503:
            throw HttpException("503 Service Unavailable: 서버가 사용 불가능한 상태", httpCode);

        default:
            throw HttpException("HTTP 요청 실패 (코드: " + std::to_string(httpCode) + ")", httpCode);
    }

    return true; // 성공
}

std::string HttpClient::urlDecode(const std::string& encoded) {
    std::ostringstream decoded;
    size_t length = encoded.length();

    for (size_t i = 0; i < length; i++) {
        if (encoded[i] == '%' && i + 2 < length) {
            std::istringstream hexStream(encoded.substr(i + 1, 2));
            int hexValue;
            if (hexStream >> std::hex >> hexValue) {
                decoded << static_cast<char>(hexValue);
                i += 2; // `%XX` 부분을 건너뜀
            } else {
                decoded << encoded[i]; // 잘못된 인코딩이면 그대로 출력
            }
        } else if (encoded[i] == '+') {
            decoded << ' '; // `+`는 공백으로 변환
        } else {
            decoded << encoded[i];
        }
    }

    return decoded.str();
}

std::string HttpClient::urlEncode(const std::string& value) {
    std::ostringstream encoded;
    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded << c;
        } else {
            encoded << '%' << std::setw(2) << std::hex << std::uppercase << (int)(unsigned char)c;
        }
    }
    return encoded.str();
}
