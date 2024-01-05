cmake_minimum_required(VERSION 3.4.1)
project(Async)
file(GLOB SRCS "*/*.h" "*/*.hpp" "*/*.cpp" "*/*.c" "*/*.cc")
add_library(Async STATIC ${SRCS})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
)

set_target_properties(Async PROPERTIES FOLDER "Runtime/Core") 
target_include_directories(Async PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

