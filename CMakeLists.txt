cmake_minimum_required(VERSION 3.18.0)
project(Wanderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

option(BUILD_SHARED_LIBS "True when building a shared library" True)

add_library(
    glad
    lib/glad/glad.h
    lib/glad/glad.c
)

include(CTest)
enable_testing()

add_executable(Wanderer main.cpp)

add_subdirectory("objImporter")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(
    Wanderer
    libglfw3.a 
    libgdi32.a
    glad
    objImporter
    )