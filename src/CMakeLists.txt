cmake_minimum_required(VERSION 3.2)

set(SOURCE_FILES main.cpp)

add_executable(bmp2arr ${SOURCE_FILES})
install(TARGETS bmp2arr DESTINATION ${BMP2ARR_INSTALL_BIN_DIR})
