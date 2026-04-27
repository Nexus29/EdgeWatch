cmake_minimum_required(VERSION 3.16)
project(EdgeWatchCore)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(core
    src/main.cpp
    src/Device.cpp
    src/Process.cpp
    src/Queue.cpp
    src/EventManager.cpp
    src/AlertLogger.cpp
    src/HttpClient.cpp
    src/ApiClient.cpp
)

# Find required packages
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

target_include_directories(core PRIVATE include)

target_link_libraries(core PRIVATE
    Threads::Threads
    CURL::libcurl
)
