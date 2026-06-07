cmake_minimum_required(VERSION 3.20)
project(LockMusicArrow)

set(CMAKE_CXX_STANDARD 23)

find_package(Geode REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

geode_add_mod(
    TARGET ${PROJECT_NAME}
)
