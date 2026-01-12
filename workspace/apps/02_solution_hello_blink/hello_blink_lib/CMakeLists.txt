# CMAKE HELLO BLINK LIB
cmake_minimum_required(VERSION 3.22)


set (HELLO_BLINK_LIB "hello_blink_lib")

set (LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (LIB_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/src/hello_blink.c)


add_library(
    ${HELLO_BLINK_LIB}
    STATIC
    ${LIB_SOURCES}
)

target_include_directories(
    ${HELLO_BLINK_LIB}
    PUBLIC 
    ${LIB_INCLUDES}
)