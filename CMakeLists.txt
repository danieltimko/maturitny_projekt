cmake_minimum_required(VERSION 3.8)
project(maturitny_projekt)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Algorithm.cpp Input.cpp Output.cpp Output.h Schedule.h Output.h Input.h)
add_executable(maturitny_projekt ${SOURCE_FILES})