cmake_minimum_required(VERSION 3.20)

project(LTSimulationEngine LANGUAGES CXX CUDA C)

message(STATUS ${SHADER_EMBEDDED_FILES})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(OpenGL REQUIRED)
add_executable(WinTMux 
    #Core/KeyCodes.cpp
    Core/KeyCodes.Console.cpp
    #Core/ControlSequences.cpp
    #Core/utf8.cpp
    
    #VtParser/Parser.cpp

    # Launch/Main.cpp
    
    # Workspace/Workspace.cpp
    # Workspace/Tree.cpp
    # Workspace/Terminal.cpp

    # MainWindow/MainWindow.cpp
    # MainWindow/CommandLine.cpp
    # MainWindow/IOverlay.cpp
    # MainWindow/TerminalSelectorOverlay.cpp
    # MainWindow/WorkspaceSelectorOverlay.cpp

    Launch/ConsoleMain.cpp
    PseudoConsole/PTYProcess.cpp

    # Console/TerminalWindow.cpp
    Console/FrameBuffer.cpp

    Platform/Application.cpp
    Platform/IOStream.cpp

    UI/UI.cpp
    UI/Workspace.cpp
)

#message(STATUS ${OpenGL_LIBRARIES})
#set(MONO_PATH "C:/GitLab/SpockEngine/ThirdParty/mono/lib/Debug")

target_link_libraries(WinTMux PRIVATE
    imgui
    glfw
    fmt
    OpenGL::GL
)

#target_compile_definitions(LTSimulationEngineRuntime PUBLIC LTSimulationEngineRuntime )
#target_compile_options(LTSimulationEngineRuntime PRIVATE
#    $<$<COMPILE_LANGUAGE:CUDA>: --expt-relaxed-constexpr -Xcudafe "--_error_number --diag_suppress=\"20012,20044\"">
#    $<$<COMPILE_LANGUAGE:CXX>:/bigobj /wd4068>)

