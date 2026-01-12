
cmake_minimum_required(VERSION 3.20)

project(
    cmake_demo
    VERSION 1.0.0
    DESCRIPTION "Classis first cmake"
    LANGUAGES C
)

set (MY_LIB "mylib")
set (C_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/say_hello.c)
set (LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create static library
add_library(
    ${MY_LIB}
    STATIC
    ${C_SOURCES}
)

target_include_directories(
    ${MY_LIB}
    PUBLIC
    ${LIB_INCLUDES}
)


add_executable(
    ${PROJECT_NAME}
    src/main.c
)


target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${MY_LIB}
)