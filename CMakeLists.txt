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
find_package(SDL2_mixer REQUIRED)

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
    GLU
    SDL2_mixer
)

# Copy assets to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})