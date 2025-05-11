cmake_minimum_required(VERSION 3.25)
project(far.cert.plugin LANGUAGES C)

include(ExternalProject)

if ((NOT CMAKE_BUILD_TYPE MATCHES Debug) AND (NOT CMAKE_BUILD_TYPE MATCHES Release))
  message(FATAL_ERROR "Invalid build type. Allowed values are Debug or Release")
endif ()

set(OPENSSL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/openssl)
set(OPENSSL_BINARY_DIR ${CMAKE_BINARY_DIR}/openssl-build)
set(OPENSSL_INSTALL_DIR ${CMAKE_BINARY_DIR}/openssl)
set(OPENSSL_CONFIGURE_ARGS --prefix=${OPENSSL_INSTALL_DIR} --openssldir=${OPENSSL_INSTALL_DIR} no-apps no-tests no-shared no-docs)

# DEBUG options
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(OPENSSL_CONFIGURE_ARGS --debug ${OPENSSL_CONFIGURE_ARGS})
endif()

# RELEASE options
if (CMAKE_BUILD_TYPE MATCHES Release)
  set(OPENSSL_CONFIGURE_ARGS --release ${OPENSSL_CONFIGURE_ARGS})
endif()

#message("C flags: ${CMAKE_C_FLAGS}")
#message("C flags Release: ${CMAKE_C_FLAGS_RELEASE}")
#message("C flags Debug: ${CMAKE_C_FLAGS_DEBUG}")
#message("Linker flags: ${CMAKE_EXE_LINKER_FLAGS}")
#message("Linker flags Release: ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
#message("Linker flags Debug: ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")

ExternalProject_Add(
  openssl
  SOURCE_DIR ${OPENSSL_SOURCE_DIR}
  BINARY_DIR ${OPENSSL_BINARY_DIR}
  INSTALL_DIR ${OPENSSL_INSTALL_DIR}
  CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/Configure ${OPENSSL_CONFIGURE_ARGS}
  BUILD_COMMAND make
  INSTALL_COMMAND make install_sw
  LOG_CONFIGURE 1
  LOG_BUILD 1
  LOG_INSTALL 1
)

SET(src
  src/main.c
)

add_executable(${CMAKE_PROJECT_NAME} ${src})

add_dependencies(${CMAKE_PROJECT_NAME} openssl)
