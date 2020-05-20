cmake_minimum_required(VERSION 3.13)
project(rzledapp VERSION 1.1)

#Disable in source-builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(RZAPP_BIN_DIR "${CMAKE_BINARY_DIR}../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RZAPP_BIN_DIR})

# --------------------  Sources --------------------
file(GLOB_RECURSE CXX_SOURCES RELATIVE  ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE C_SOURCES RELATIVE    ${CMAKE_SOURCE_DIR} "src/*.c")
include_directories("include/")
include_directories("src/")

add_executable(rzledapp ${CXX_SOURCES}  ${C_SOURCES})
