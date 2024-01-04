cmake_minimum_required(VERSION 3.4.1)
project(Math)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)
file(GLOB HEADS  "*/*.h" "*/*.hpp")
add_library(Math STATIC ${src} ${HEADS})

#set(CMAKE_CXX_FLAGS "-std=c++20")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RUNTIME_CORE_DIR}/include
    ${RUNTIME_CONTAINERS_DIR}/include
    ${RUNTIME_THIRD_PART_DIR}
)

set_target_properties(Math PROPERTIES FOLDER "Runtime/Core") 
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
