include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file (GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


list(REMOVE_ITEM SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

file (GLOB_RECURSE TEST_FILES
    "*.h"
    "*.cpp"
)

add_executable(
    ProducerTests
    ${TEST_FILES}
    ${SRC_FILES}
)

target_include_directories(
    ProducerTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
    ProducerTests
    PRIVATE
        GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(ProducerTests)
