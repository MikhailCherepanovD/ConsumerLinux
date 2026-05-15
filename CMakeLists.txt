cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    Consumer                        
    VERSION 0.0.1
    DESCRIPTION "Consumer"

    LANGUAGES CXX
)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
