#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <stdexcept>

/**
 * 
 * Config& config = Config::getInstance();
 * 
 */
class Config {
public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    void load(const std::string& filename);
    std::string get(const std::string& key);
    int getInt(const std::string& key);
    void print();

    // 복사 & 이동 금지
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

private:
    std::map<std::string, std::string> data;  // "섹션.키" = 값

    Config() {}  // private 생성자 (외부에서 직접 생성 불가)

    void replaceEnvVars(std::string &input);
    void replaceInternalVars(std::string &input, const std::string& section);
};

#endif // CONFIG_H
