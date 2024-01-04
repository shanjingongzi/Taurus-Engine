cmake_minimum_required(VERSION 3.4.1)
project(NavigationSystem)
file(GLOB SRCS "*/*.h" "*/*.hpp" "*/*.inl"  "*/*.cpp" "*/*.c" "*/*.cc")
add_library(NavigationSystem  ${SRCS})
#set(CMAKE_CXX_FLAGS "-std=c++20")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${RUNTIME_THIRD_PART_DIR}
    ${RUNTIME_MATH_DIR}/include
)
set_target_properties(NavigationSystem PROPERTIES FOLDER "Runtime/Core")
target_include_directories(NavigationSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
