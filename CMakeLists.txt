cmake_minimum_required(VERSION 3.2)

project(bmp2arr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BMP2ARR_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(BMP2ARR_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/build)


include_directories(${BMP2ARR_INSTALL_INCLUDE_DIR})

add_subdirectory(src)


