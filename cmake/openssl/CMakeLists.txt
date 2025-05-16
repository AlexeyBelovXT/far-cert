cmake_minimum_required(VERSION 3.25)
project(openssl LANGUAGES NONE)

include(ExternalProject)

if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(FATAL_ERROR "Invalid build type. Allowed values are Debug or Release")
endif ()

if (NOT OPENSSL_SOURCE_DIR)
    message(FATAL_ERROR "OPENSSL_SOURCE_DIR is not defined")
endif()

set(OPENSSL_TMP_DIR ${CMAKE_BINARY_DIR}/openssl-ep-tmp)
set(OPENSSL_STAMP_DIR ${CMAKE_BINARY_DIR}/openssl-ep-stamp)
set(OPENSSL_BINARY_DIR ${CMAKE_BINARY_DIR}/openssl-ep-build)
set(OPENSSL_INSTALL_DIR ${CMAKE_BINARY_DIR}/openssl)
set(OPENSSL_CONFIGURE_ARGS --prefix=${OPENSSL_INSTALL_DIR} --openssldir=${OPENSSL_INSTALL_DIR} no-apps no-tests no-shared no-docs)

# OPENSSL commands for UNIX
if (UNIX)
    set(OPENSSL_CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/Configure ${OPENSSL_CONFIGURE_ARGS})
    set(OPENSSL_BUILD_COMMAND make)
    set(OPENSSL_INSTALL_COMMAND make install_sw)
endif()

# OPENSSL commands for WIN32
if (WIN32)
    set(OPENSSL_CONFIGURE_COMMAND perl ${OPENSSL_SOURCE_DIR}/Configure ${OPENSSL_CONFIGURE_ARGS})
    set(OPENSSL_BUILD_COMMAND nmake)
    set(OPENSSL_INSTALL_COMMAND nmake install_sw)
endif()

# DEBUG options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPENSSL_CONFIGURE_ARGS --debug ${OPENSSL_CONFIGURE_ARGS})
endif()

# RELEASE options
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPENSSL_CONFIGURE_ARGS --release ${OPENSSL_CONFIGURE_ARGS})
endif()

# OPENSSL
ExternalProject_Add(
    openssl-ep
    TMP_DIR ${OPENSSL_TMP_DIR}
    STAMP_DIR ${OPENSSL_STAMP_DIR}
    SOURCE_DIR ${OPENSSL_SOURCE_DIR}
    BINARY_DIR ${OPENSSL_BINARY_DIR}
    INSTALL_DIR ${OPENSSL_INSTALL_DIR}
    CONFIGURE_COMMAND ${OPENSSL_CONFIGURE_COMMAND}
    BUILD_COMMAND ${OPENSSL_BUILD_COMMAND}
    INSTALL_COMMAND ${OPENSSL_INSTALL_COMMAND}
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)

add_library(openssl INTERFACE)
add_dependencies(openssl openssl-ep)
target_include_directories(openssl INTERFACE ${OPENSSL_INSTALL_DIR}/include)

if (UNIX)
    set_property(TARGET openssl PROPERTY INTERFACE_LINK_LIBRARIES
        ${OPENSSL_INSTALL_DIR}/lib/libcrypto.a
        ${OPENSSL_INSTALL_DIR}/lib/libssl.a
    )
endif()

if (WIN32)
    set_property(TARGET openssl PROPERTY INTERFACE_LINK_LIBRARIES
        ${OPENSSL_INSTALL_DIR}/lib/libcrypto.lib
        ${OPENSSL_INSTALL_DIR}/lib/libssl.lib
    )
endif()