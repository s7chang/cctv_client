# 컴파일러 설정
CC = g++
CFLAGS = -Wall -std=c++17 `pkg-config --cflags libavformat libavcodec libavutil libswscale`
LDFLAGS = `pkg-config --libs libavformat libavcodec libavutil libswscale` -lcurl -lpugixml -pthread

# 디렉토리 설정
SRC_DIR = .
BUILD_DIR = ../build

# 소스 파일 및 객체 파일 설정
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# 실행 파일 이름
TARGET = $(BUILD_DIR)/cctv_client

# 기본 빌드 규칙 (첫 번째 규칙: 실행 파일을 목표로 설정)
all: $(TARGET)

# 실행 파일 빌드 (모든 오브젝트 파일을 링크하여 실행 파일 생성)
$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 개별 오브젝트 파일 빌드 (각 소스 파일을 빌드 디렉토리에 컴파일)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# 빌드 디렉토리 생성 (명시적으로 실행되도록 변경)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 정리(clean) 명령 (빌드된 모든 파일 삭제)
clean:
	rm -rf $(BUILD_DIR)
