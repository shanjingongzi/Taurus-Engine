cmake_minimum_required(VERSION 3.4.1)
PROJECT(RHI)
set(CMAKE_CXX_FLAGS "-std=c++20 ")
file(GLOB src "*.h" "*.cpp" "*/*.h" "*/*.cpp" "*/*hpp")
add_library(RHI ${src})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RUNTIME_CORE_DIR}/include
)
