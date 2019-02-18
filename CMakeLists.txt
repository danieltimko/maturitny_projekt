cmake_minimum_required(VERSION 3.8)
project(maturitny_projekt)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Algorithm.cpp src/Input.cpp src/Output.cpp include/Output.h include/Schedule.h include/Output.h include/Input.h)
add_executable(maturitny_projekt ${SOURCE_FILES})