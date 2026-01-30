cmake_minimum_required(VERSION 3.24)

# MUST be set before project() to take effect
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Enable policy to support CMAKE_MSVC_RUNTIME_LIBRARY with Clang
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

set(CMAKE_CXX_STANDARD 20)

# Prefer static libraries and static runtime by default
set(BUILD_SHARED_LIBS OFF)
set(GLFW_LIBRARY_TYPE STATIC)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        set(VCPKG_TARGET_TRIPLET "x64-windows-static")
    endif()
endif()

if(UNIX)
    set(CMAKE_TOOLCHAIN_FILE "~/Development/vcpkg/scripts/buildsystems/vcpkg.cmake")
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        if(APPLE)
            set(VCPKG_TARGET_TRIPLET "x64-osx")
        else()
            set(VCPKG_TARGET_TRIPLET "x64-linux-static")
        endif()
    endif()
endif()
 
# Specify the project name
project(NiftyScallop)

# Force static runtime for Clang on Windows using correct flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND WIN32)
    # Replace dynamic runtime flags with static runtime
    string(REPLACE "-D_DLL" "-D_MT" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "--dependent-lib=msvcrtd" "--dependent-lib=libcmtd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "-D_DLL" "-D_MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "--dependent-lib=msvcrt" "--dependent-lib=libcmt" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    
    # Set linker options with proper -Xlinker prefix
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker /NODEFAULTLIB:msvcrtd.lib -Xlinker /DEFAULTLIB:libcmtd.lib")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker /NODEFAULTLIB:msvcrt.lib -Xlinker /DEFAULTLIB:libcmt.lib")
endif()

#include(FetchContent)
#FetchContent_Declare(
#   lunasvg
#    GIT_REPOSITORY https://github.com/sammycage/lunasvg.git
#    GIT_TAG master  # Specify the desired branch or tag
#)
#FetchContent_MakeAvailable(lunasvg)

#FetchContent_Declare(
#    glfw
#    GIT_REPOSITORY https://github.com/glfw/glfw.git
#    GIT_TAG latest
#)
#FetchContent_MakeAvailable(glfw)

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(lunasvg CONFIG REQUIRED)
#find_package(NiftyLib CONFIG REQUIRED)

add_subdirectory(NiftyLib)

include_directories("src/include")

file(GLOB SOURCES "src/*.cpp")

add_executable(NiftyScallop ${SOURCES})

if(UNIX AND NOT APPLE)
    target_link_options(NiftyScallop PRIVATE -static -static-libgcc -static-libstdc++)
endif()

if (WIN32)
    target_link_libraries(NiftyScallop PRIVATE opengl32 gdi32 user32 shell32)
endif()

target_link_libraries(NiftyScallop PRIVATE NiftyLib lunasvg::lunasvg imgui::imgui glfw glad::glad)