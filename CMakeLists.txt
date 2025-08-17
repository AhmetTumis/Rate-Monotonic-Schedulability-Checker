cmake_minimum_required(VERSION 3.22)
project(RMSChecker)
set (CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(RMSChecker src/main.cpp src/RMS.cpp)

