cmake_minimum_required(VERSION 3.25)
project(far-cert LANGUAGES C)

if (NOT WIN32)
    message(FATAL_ERROR "Target system is not Windows")
endif()

if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(FATAL_ERROR "Invalid build type. Allowed values are Debug or Release")
endif ()

# openssl
set(OPENSSL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/openssl)
add_subdirectory(cmake/openssl)

# far
add_subdirectory(cmake/far)

SET(src
    src/main.c
    src/cert.def
)

add_library(cert MODULE ${src})

target_link_libraries(cert
    openssl
    far
    Ws2_32.lib
    Crypt32.lib
)

set_target_properties(cert
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${FAR_MANAGER_PLUGINS_DIR}/Cert
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${FAR_MANAGER_PLUGINS_DIR}/Cert
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${FAR_MANAGER_PLUGINS_DIR}/Cert
)
