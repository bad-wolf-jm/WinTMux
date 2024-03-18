cmake_minimum_required(VERSION 3.20)

project(wtmux LANGUAGES CXX CUDA C)

message(STATUS ${SHADER_EMBEDDED_FILES})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(OpenGL REQUIRED)
add_executable(wtmux 
    Core/KeyCodes.Console.cpp
    
    VtParser/Parser.cpp
    VtParser/utf8.cpp

    Launch/ConsoleMain.cpp
    Platform/process.cpp
    Platform/console.cpp
    Platform/pipe.cpp

    Console/FrameBuffer.cpp

    Platform/Application.cpp
    Platform/stdout.cpp
    Platform/stdin.cpp

    UI/UI.cpp
)

target_link_libraries(wtmux PRIVATE
    fmt
)
