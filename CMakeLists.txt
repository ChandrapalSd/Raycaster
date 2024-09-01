cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Raycaster)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
# Add Raylib as a subdirectory
add_subdirectory("C:/raylib/raylib" ${CMAKE_BINARY_DIR}/raylib_build)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Glob for .cpp and .hpp files
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

# Our Project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Set the default target
add_custom_target(default ALL DEPENDS ${PROJECT_NAME})
