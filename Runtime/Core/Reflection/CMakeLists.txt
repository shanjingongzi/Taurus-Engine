cmake_minimum_required(VERSION 3.4.1)
project(Reflection)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)
file(GLOB HEADS  "*/*.h" "*/*.hpp")
add_library(Reflection ${src} ${HEADS})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RUNTIME_CORE_DIR}/include
)

set_target_properties(Reflection PROPERTIES FOLDER "Runtime/Core") 
target_include_directories(Reflection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
