cmake_minimum_required(VERSION 3.25)
project(far LANGUAGES NONE)

file(DOWNLOAD "https://farmanager.com/files/Far30b6446.x64.20250301.7z" ${CMAKE_BINARY_DIR}/far/far.7z)
file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/far/far.7z DESTINATION ${CMAKE_BINARY_DIR}/far)
file(COPY ${CMAKE_BINARY_DIR}/far/PluginSDK/Headers.c/plugin.hpp DESTINATION ${CMAKE_BINARY_DIR}/far-sdk/far)
file(COPY ${CMAKE_BINARY_DIR}/far/PluginSDK/Headers.c/farcolor.hpp DESTINATION ${CMAKE_BINARY_DIR}/far-sdk/far)

add_library(far INTERFACE)
target_include_directories(far INTERFACE ${CMAKE_BINARY_DIR}/far-sdk)