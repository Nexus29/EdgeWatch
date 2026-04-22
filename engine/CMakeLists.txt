cmake_minimum_required(VERSION 3.16)
project(EdgeWatchCore)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(core
    src/main.cpp
    src/Device.cpp
    src/Process.cpp
)
