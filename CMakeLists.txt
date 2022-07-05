cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME keyboard-layout-skip)
project(${PROJECT_NAME})
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${PROJECT_NAME} ${srcs} ${hdrs})