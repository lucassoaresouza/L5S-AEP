cmake_minimum_required(VERSION 3.1)
project(aep LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)                                                                                                                                 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output binary directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

# Make sure the binary directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# Tell CMake to put executables in the binary directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Creating variables
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(ASSETS "${PROJECT_SOURCE_DIR}/assets")
set(ENGINE "${PROJECT_SOURCE_DIR}/engine")
set(COMPILER "${PROJECT_SOURCE_DIR}/compiler")
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Setting COMPILE_FLAGS (this is from CMAKE)
set(COMPILE_FLAGS "-std=c++11 -W -std=c++0x -Wall -pedantic -Wshadow -O2 -g")

# Adding subdirectory which has it's own CMakeList
add_subdirectory(${ENGINE})
add_subdirectory(${COMPILER})

# Including header files
include_directories(${INCLUDE_DIR})

# Creating executable and adding libraries to CMake
add_executable(aep ${SOURCES})
set_property(TARGET aep PROPERTY CXX_STANDARD 11)
target_link_libraries(aep engine compiler SDL2 SDL2_image SDL2_ttf SDL2_mixer)
