cmake_minimum_required(VERSION 3.4.1)
PROJECT(Engine)
aux_source_directory(${cmake_current_source_dir}/src SRCS)
file(GLOB HEADS "*/*.h" "*/*.cpp")
add_library(Engine STATIC ${SRCS} ${HEADS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
	${RUNTIME_CORE_DIR}/include
	${RUNTIME_MATH_DIR}/include
	${RUNTIME_CONTAINERS_DIR}/include
	${RUNTIME_MODULE_DIR}/include
	${RUNTIME_THIRD_PARTY}
)

set_target_properties(Engine PROPERTIES FOLDER "Runtime") 
link_directories(${CMAKE_CURRENT_SOURCE_DIR}../../Bin)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries(Engine PRIVATE RenderCore OpenGLRender )
