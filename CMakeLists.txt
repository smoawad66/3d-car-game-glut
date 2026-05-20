cmake_minimum_required(VERSION 3.10)
project(CarGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set OpenGL preference to GLVND to suppress warnings
cmake_policy(SET CMP0072 NEW)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)

# Handle SDL2_mixer differently on Windows
if(WIN32)
    # Try to find SDL2_mixer using pkg-config first (vcpkg provides this)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2_MIXER SDL2_mixer)
    endif()
    
    # If pkg-config didn't work, try manual search
    if(NOT SDL2_MIXER_FOUND)
        find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
            HINTS
            ${SDL2_DIR}
            $ENV{SDL2_DIR}
            PATH_SUFFIXES include/SDL2 include SDL2
        )
        
        find_library(SDL2_MIXER_LIBRARY
            NAMES SDL2_mixer
            HINTS
            ${SDL2_DIR}
            $ENV{SDL2_DIR}
            PATH_SUFFIXES lib lib/x64 lib/x86
        )
        
        if(SDL2_MIXER_INCLUDE_DIR AND SDL2_MIXER_LIBRARY)
            set(SDL2_MIXER_FOUND TRUE)
            set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})
            set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
        endif()
    endif()
    
    if(NOT SDL2_MIXER_FOUND)
        message(FATAL_ERROR "SDL2_mixer not found on Windows. Please install via vcpkg: vcpkg install sdl2-mixer:x64-windows")
    endif()
else()
    # Linux - use the original method that works
    find_package(SDL2_mixer REQUIRED)
endif()

# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Create executable
add_executable(car_game ${SOURCES})

# Link libraries
target_link_libraries(car_game
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    OpenGL::GLU
    SDL2_mixer
)

# Copy assets to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})