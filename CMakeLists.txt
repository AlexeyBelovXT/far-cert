cmake_minimum_required(VERSION 3.25)
project(far.cert.plugin LANGUAGES C)

# ../deps/openssl/Configure --debug no-tests no-shared


SET(src
  src/main.c
)

add_executable(${CMAKE_PROJECT_NAME} ${src})
