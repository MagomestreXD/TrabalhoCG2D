cmake_minimum_required(VERSION 3.20)

project(MeuJogo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(MeuJogo
    src/main.cpp
    src/rasterizer.cpp
)

target_include_directories(MeuJogo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MeuJogo PRIVATE SDL3::SDL3)
