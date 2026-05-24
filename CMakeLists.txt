cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    Consumer                        
    VERSION 0.0.1
    DESCRIPTION "Consumer"

    LANGUAGES CXX
)

file (GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.cpp"
)

add_executable (
    ${PROJECT_NAME}
    ${SRC_FILES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)
