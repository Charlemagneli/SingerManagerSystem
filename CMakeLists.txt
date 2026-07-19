cmake_minimum_required(VERSION 3.20)
project(SingerManagerSystem)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(
    SingerManagerSystem

    src/main.cpp
    src/SystemManager.cpp
)