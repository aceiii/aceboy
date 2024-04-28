cmake_minimum_required(VERSION 3.15)

project(aceboy VERSION 0.0.1 LANGUAGES CXX)

set(EXE_NAME aceboy)

set(SOURCE_FILES
    src/main.cpp
)

add_executable(${EXE_NAME} ${SOURCE_FILES})

