#include "config.h"
#include <cstdlib> // std::stoi

static std::regex s_regexEnv(R"(\$\{?([A-Za-z_][A-Za-z0-9_]*)\}?)");    // ${VAR} 또는 $VAR 처리
static std::regex s_regexInternal(R"(\{([A-Za-z0-9_.]+)\})");           // {VAR} 처리

// 환경 변수 치환 (없으면 오류 발생)
void Config::replaceEnvVars(std::string &input) {
    std::smatch match;
    while (std::regex_search(input, match, s_regexEnv)) {
        std::string varName = match[1].str();
        const char* envValue = std::getenv(varName.c_str());

        if (!envValue) {
            throw std::runtime_error("환경 변수 '" + varName + "'을(를) 찾을 수 없습니다.");
        }
        std::string envValueStr = std::string(envValue);
        // if (envValueStr.empty()) {
        //     throw std::runtime_error("환경 변수 '" + varName + "'이(가) 빈 값입니다.");
        // }

        input.replace(match.position(0), match.length(0), envValueStr);
    }
}

// 내부 변수 치환 (없으면 오류 발생)
void Config::replaceInternalVars(std::string &input, const std::string& section) {
    std::smatch match;
    while (std::regex_search(input, match, s_regexInternal)) {
        std::string varName = match[1].str();
        auto it = data.find(varName);
        if (it == data.end()) {
            if (!section.empty()) {
                it = data.find(section + '.' + varName);
            }
            if (it == data.end()) {
                throw std::runtime_error("설정 변수 '" + varName + "'을(를) 찾을 수 없습니다.");
            }
        }
        input.replace(match.position(0), match.length(0), it->second);
    }
}

// 설정 파일 로드
void Config::load(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, section;

    if (!file) {
        throw std::runtime_error("설정 파일 '" + filename + "'을(를) 찾을 수 없습니다.");
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // 빈 줄 및 주석 무시
        if (line[0] == '[' && line.back() == ']') {
            section = line.substr(1, line.length() - 2); // 섹션 이름 저장
            continue;
        }

        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) continue; // '=' 없는 라인 무시

        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);

        // 양쪽 공백 제거
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        std::string fullKey = section.empty() ? key : section + "." + key;  // 섹션.키 형식
        try {
            replaceEnvVars(value);      // 1. 환경 변수 치환
            replaceInternalVars(value, section); // 2. 내부 변수 치환

            // 치환이 완료된 값을 맵에 저장
            data[fullKey] = value;

        } catch (const std::runtime_error& e) {
            std::cerr << "설정 파일 오류: " << e.what() << std::endl;
            exit(1);
        }
    }
}

// 문자열 값을 가져오기
std::string Config::get(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    throw std::runtime_error("'" + key + "' 키를 찾을 수 없습니다.");
}

// 정수 값을 가져오기 (`getInt()`)
int Config::getInt(const std::string& key) {
    std::string value = get(key);
    try {
        return std::stoi(value);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("'" + key + "' 값이 정수가 아닙니다.");
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("'" + key + "' 값이 정수 범위를 초과했습니다.");
    }
}

// 변수 출력
void Config::print() {
    std::cout << "=== 변수 목록 ===" << std::endl;
    std::string currentSection;

    for (const auto& pair : data) {
        std::string fullKey = pair.first;

        // 뒤에서부터 `.`을 찾아 섹션과 키를 분리
        size_t dotPos = fullKey.rfind('.');

        std::string section = (dotPos != std::string::npos) ? fullKey.substr(0, dotPos) : "";
        std::string key = (dotPos != std::string::npos) ? fullKey.substr(dotPos + 1) : fullKey;

        // 섹션이 변경되었을 경우 출력
        if (section != currentSection) {
            std::cout << std::endl << "[" << section << "]" << std::endl;
            currentSection = section;
        }

        std::cout << key << " = " << pair.second << std::endl;
    }
}
