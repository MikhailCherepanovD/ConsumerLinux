file (GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)

add_executable (
    ${PROJECT_NAME}
    ${SRC_FILES}
)

