cmake_minimum_required(VERSION 3.21.1)

set(BUILD_QDS_COMPONENTS ON CACHE BOOL "Build design studio components")

project(EditorApp LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTTargets")
set_property(GLOBAL PROPERTY CMAKE_AUTOMOC_COMPILER_PREDEFINES "StuidoComponent")
set_property(GLOBAL PROPERTY CMAKE_VS_PLATFORM_NAME_DEFAULT "StuidoComponent")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules")
find_package(ASSIMP REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS Gui Qml Quick)
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)

add_subdirectory(${ROOT_DIR}/Runtime Runtime.out)
# To build this application you need Qt 6.2.0 or higher
if (Qt6_VERSION VERSION_LESS 6.2.0)
message(FATAL_ERROR "You need Qt 6.2.0 or newer to build the application.")
endif()

qt_add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    ./include/OpenGLDevice.h
    ./include/OpenGLRenderer.h
    ./include/OpenGLRenderImp.h
    ./include/OpenGLViewport.h
    ./src/OpenGLDevice.cpp
    ./src/OpenGLRenderer.cpp
    ./src/OpenGLRenderImp.cpp
    ./src/OpenGLViewport.cpp
    ./src/OpenGLDevicePart.cpp
)


set_target_properties(
    ${CMAKE_PROJECT_NAME}  PROPERTIES FOLDER "Program.Editor"
)

# qt_standard_project_setup() requires Qt 6.3 or higher. See https://doc.qt.io/qt-6/qt-standard-project-setup.html for details.
if (${QT_VERSION_MINOR} GREATER_EQUAL 3)
qt6_standard_project_setup()
endif()

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${ROOT_DIR}/ThirdParty
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
    ${ASSIMP_LIBRARY}
    Core
    Engine
    RenderCore
    OpenGLRender
    Math
    Containers
    Launch
)


if (${BUILD_QDS_COMPONENTS})
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)
