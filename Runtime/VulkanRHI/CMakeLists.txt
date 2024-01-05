cmake_minimum_required(VERSION 3.4.1)
PROJECT(VulkanRHI)
set(CMAKE_CXX_FLAGS "-std=c++20 ")
file(GLOB src "*.h" "*.cpp" "*/*.h" "*/*.cpp")
add_library(VulkanRHI ${src})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RUNTIME_THIRD_PART_DIR}
    ${RUNTIME_CORE_DIR}/include
    ${RUNTIME_CONTAINERS_DIR}/include
    ${RUNTIME_RHI_DIR}/include
    ${RUNTIME_VULKAN_DIR}/Include
)