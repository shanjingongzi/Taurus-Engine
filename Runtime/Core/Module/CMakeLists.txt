cmake_minimum_required(VERSION 3.4.1)
project(Module)
file(GLOB SRCS "*/*.h" "*/*.hpp" "*/*.inl"  "*/*.cpp" "*/*.c" "*/*.cc")
add_library(Module  ${SRCS})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${RUNTIME_THIRD_PART_DIR}
)
set_target_properties(Module PROPERTIES FOLDER "Runtime/Core")
target_include_directories(Module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
