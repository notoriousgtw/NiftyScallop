cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(VCPKG_CMAKE_CONFIGURE_OPTIONS -DBUILD_SHARED_LIBS=OFF -DUSE_MSVC_RUNTIME_LIBRARY_DLL=ON)
 
# Static runtime for MSVC
if(MSVC)
    foreach(flag_var
        CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_DEBUG)
        string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endforeach()
endif()

# Specify the project name
project(NiftyScallop)

include(FetchContent)
FetchContent_Declare(
    lunasvg
    GIT_REPOSITORY https://github.com/sammycage/lunasvg.git
    GIT_TAG master  # Specify the desired branch or tag
)
FetchContent_MakeAvailable(lunasvg)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Find libxlsxwriter's include directory
find_path(XLSXWRITER_INCLUDE_DIR NAMES xlsxwriter.h HINTS ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include)

# Find libxlsxwriter's library file
find_library(XLSXWRITER_LIBRARY NAMES xlsxwriter HINTS ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/lib)

include_directories("include" ${XLSX_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")


add_executable(NiftyScallop ${SOURCES})

target_compile_definitions(NiftyScallop PRIVATE GLFW_STATIC)

if (WIN32)
    target_link_libraries(NiftyScallop PRIVATE opengl32 gdi32 user32 shell32)
endif()

target_link_libraries(NiftyScallop PRIVATE ${XLSXWRITER_LIBRARY} lunasvg::lunasvg imgui::imgui glfw glad::glad)