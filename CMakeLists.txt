cmake_minimum_required(VERSION 3.25)
project(far-cert LANGUAGES C)

include(ExternalProject)

if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
  message(FATAL_ERROR "Invalid build type. Allowed values are Debug or Release")
endif ()

set(OPENSSL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/openssl)
set(OPENSSL_BINARY_DIR ${CMAKE_BINARY_DIR}/openssl-build)
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

ExternalProject_Add(
  openssl
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

SET(src
  src/main.c
)

add_executable(${CMAKE_PROJECT_NAME} ${src})

add_dependencies(${CMAKE_PROJECT_NAME} openssl)
