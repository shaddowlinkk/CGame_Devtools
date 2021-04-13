cmake_minimum_required(VERSION 3.17)
project(CGame_Devtools C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_ttf
        REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(CGame_Devtools main.c ${CMAKE_CURRENT_SOURCE_DIR}/cmake/icon.rc)