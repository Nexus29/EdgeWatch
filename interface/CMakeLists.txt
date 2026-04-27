cmake_minimum_required(VERSION 3.16)

project(EdgeWatchUI)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Quick)

add_executable(qt-ui
    main.cpp
)

target_link_libraries(qt-ui PRIVATE Qt6::Quick)
