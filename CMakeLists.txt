cmake_minimum_required(VERSION 3.25)
project(far-cert LANGUAGES C)

if (NOT WIN32)
    message(FATAL_ERROR "Target system is not Windows")
endif()

if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(FATAL_ERROR "Invalid build type. Allowed values are Debug or Release")
endif ()

set(OPENSSL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/openssl)
add_subdirectory(cmake/openssl)

add_subdirectory(cmake/far)

SET(src
    src/main.c
)

add_library(${CMAKE_PROJECT_NAME} MODULE ${src})

add_dependencies(${CMAKE_PROJECT_NAME}
    openssl
    far
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE openssl
    PRIVATE far
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    openssl
    Ws2_32.lib
    Crypt32.lib
)

