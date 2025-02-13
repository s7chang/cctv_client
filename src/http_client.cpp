#include "http_client.h"
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool HTTPClient::checkAIStatus(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return response.find("AIX_OBJECT_DETECTION_ENABLE=1") != std::string::npos;
}

void HTTPClient::sendCommand(const std::string& url, const std::string& param) {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    std::string fullUrl = url + "?action=writeparam&" + param;

    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "HTTP request failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
}
