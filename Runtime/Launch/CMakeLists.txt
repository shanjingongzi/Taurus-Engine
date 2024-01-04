cmake_minimum_required(VERSION 3.4.1)
project(Launch)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)
file(GLOB HEADS  "*/*.h" "*/*.hpp")
add_library(Launch STATIC ${src} ${HEADS})
#set(CMAKE_CXX_FLAGS "-std=c++20")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Launch Engine)
set_target_properties(Launch PROPERTIES FOLDER "Runtime") 
target_include_directories(Launch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

