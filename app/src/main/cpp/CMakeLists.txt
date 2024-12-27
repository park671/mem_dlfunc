cmake_minimum_required(VERSION 3.22.1)
project("dlfunc")

enable_language(ASM)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS S)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS -O0)
set(CMAKE_CXX_FLAGS -O0)

file(GLOB_RECURSE
        DL_FUNC_DIR
        "*.c"
        "*.cpp" "*.cc" "*.S" "*.s"
)

add_library(
        ${CMAKE_PROJECT_NAME}
        SHARED
        ${DL_FUNC_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)
