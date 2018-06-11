cmake_minimum_required(VERSION 3.7.2)
project(zappy)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)

include_directories(include)
file(GLOB_RECURSE INCLUDES include/*.h)
file(GLOB_RECURSE SOURCES srcs/*.c)

add_executable(${PROJECT_NAME}
        ${INCLUDES}
        ${SOURCES})