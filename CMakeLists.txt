cmake_minimum_required(VERSION 3.15)

project(aceboy VERSION 0.0.1 LANGUAGES CXX)

set(EXE_NAME aceboy)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(TOML_EXCEPTIONS=0)

set(SOURCE_FILES
    src/main.cpp
    src/interface.cpp
)

find_package(spdlog CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

add_executable(${EXE_NAME} ${SOURCE_FILES})

target_link_libraries(${EXE_NAME} PRIVATE
    spdlog::spdlog
    argparse::argparse
    magic_enum::magic_enum
    imgui::imgui
    raylib
)
