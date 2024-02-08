cmake_minimum_required(VERSION 3.20)

project(WinTMux CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(THIRD_PARTY_INSTALLATION_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/libs)

project(LeddarSimulator_ThirdParty CXX)
set(CMAKE_CXX_STANDARD 17)

set(EXTERNAL_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(IMGUI_DIR ${EXTERNAL_LIBRARY_DIR}/imgui)
include_directories(${IMGUI_DIR})

include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMGUI_DIR}/misc/cpp )

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp  
)

include_directories(
    ${EXTERNAL_LIBRARY_DIR}/imgui
)

# add_compile_definitions(ZEP_FEATURE_CPP_FILE_SYSTEM=1)
# add_subdirectory(zep/src)

# add_subdirectory(glfw)
# add_subdirectory(fmt)




# add_compile_definitions(YAML_CPP_STATIC_DEFINE)
# set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
# add_subdirectory(yaml-cpp)
