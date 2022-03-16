cmake_minimum_required(VERSION 3.20)
project(MyRenderer LANGUAGES CXX)

set(HEADERS
    Source/Core/Api.h
    Source/Core/Image.h
    Source/Core/Macro.h
    Source/Core/Platform.h
    Source/Core/Framebuffer.h
    Source/Core/Camera.h
    Source/Core/Mesh.h
    Source/Core/Graphics.h
    Source/Math/Math.h
    Source/Math/Matrix.h
    Source/Math/Quat.h
    Source/Math/Vector.h
    Source/Scene/Model.h
    Source/Scene/Scene.h
    Source/Scene/Cache.h
    Source/Launch/Blinn.h
)

set(SOURCES
    Source/Main.cpp
    Source/Core/Image.cpp
    Source/Core/Framebuffer.cpp
    Source/Core/Camera.cpp
    Source/Core/Mesh.cpp
    Source/Core/Graphics.cpp
    Source/Math/Math.cpp
    Source/Math/Matrix.cpp
    Source/Math/Vector.cpp
    Source/Math/Quat.cpp
    Source/Scene/Model.cpp
    Source/Scene/Scene.cpp
    Source/Scene/Cache.cpp
    Source/Launch/Blinn.cpp
)

if (WIN32)
    set(SOURCES ${SOURCES} Source/Platform/Win32.cpp)
endif()

set(TARGET Viewer)
add_executable(${TARGET} ${HEADERS} ${SOURCES})

# ------------------------------------------------------
# Compile options
# ------------------------------------------------------
if(MSVC)
    target_compile_options(${TARGET} PRIVATE /W4 /D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(${TARGET} PRIVATE /fp:fast)
else()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(${TARGET} PRIVATE -ffast-math)
endif()

# ------------------------------------------------------
# IDE Settings
# ------------------------------------------------------
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ${TARGET})
source_group(TREE "${CMAKE_SOURCE_DIR}/Source" FILES ${HEADERS} ${SOURCES})
