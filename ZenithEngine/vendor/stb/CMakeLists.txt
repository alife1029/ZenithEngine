cmake_minimum_required(VERSION 3.5)

project(stb)
file(GLOB STB_SOURCES src/**.c)
add_library(${PROJECT_NAME} ${STB_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
