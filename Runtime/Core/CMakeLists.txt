cmake_minimum_required(VERSION 3.4.1)
project(Core)
file(GLOB SRCS "*/*.h" "*/*.hpp" "*/*.inl"  "*/*.cpp" "*/*.c" "*/*.cc")
add_library(Core STATIC ${SRCS})
add_subdirectory(Math)
add_subdirectory(Containers)
add_subdirectory(Async)
add_subdirectory(Reflection)
#set(CMAKE_CXX_FLAGS "-std=c++20")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${RUNTIME_THIRD_PART_DIR}
)
set_target_properties(Core PROPERTIES FOLDER "Runtime/Core")
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Containers)
