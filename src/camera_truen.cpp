#include "camera_truen.h"
#include <iostream>

void trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

bool CameraTruen::readConfig(const std::string& param, std::string& response) const {
    std::string url = protocol + "://" + addr + "/httpapx/ReadParam?action=readparam&" + param + "=&";
    bool result = HttpClient::sendRequest(protocol, "GET", url, username, passwd, &response);
    if (result) {
        // 응답이 "param=value" 형태로 오기 때문에 해당 부분을 검사하고 "value" 부분만 추출
        size_t pos = response.find(param + '=');
        if (pos != std::string::npos) {
            response = response.substr(pos + param.size() + 1); // '=' 다음 문자열만 남김
            trim(response);
        }
        else {
            result = false;
        }
    }
    return result;
}

bool CameraTruen::writeConfig(const std::string& param, const std::string& value) const {
    std::string url = protocol + "://" + addr + "/httpapx/WriteParam?action=writeparam&" + param + "=" + value + "&";
    return HttpClient::sendRequest(protocol, "GET", url, username, passwd);
}