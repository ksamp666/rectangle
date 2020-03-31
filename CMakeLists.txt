cmake_minimum_required(VERSION 3.13)
project(Rectangle)

set(CMAKE_CXX_STANDARD 17)

include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Rectangle main.cpp source/utils/Random.cpp source/utils/Random.h source/characters/RotatingRectangle.cpp source/characters/RotatingRectangle.h source/Config.h source/utils/FrameLogger.cpp source/utils/FrameLogger.h)

target_link_libraries (Rectangle sfml-graphics sfml-window sfml-system)