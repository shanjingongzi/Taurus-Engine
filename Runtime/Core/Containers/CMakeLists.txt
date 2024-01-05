cmake_minimum_required(VERSION 3.4.1)
project(Containers)
file(GLOB source "*/*.h" "*/*.hpp" "*/*.cpp" "*/*.c" "*/*.cc")
add_library(Containers STATIC ${source})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${RUNTIME_CORE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty
)

set_target_properties(Containers PROPERTIES FOLDER "Runtime/Core") 
target_include_directories(Containers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Math)
