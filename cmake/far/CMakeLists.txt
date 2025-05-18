cmake_minimum_required(VERSION 3.25)
project(far LANGUAGES NONE)

file(DOWNLOAD "https://farmanager.com/files/Far30b6446.x64.20250301.7z" ${CMAKE_CURRENT_BINARY_DIR}/far.7z)
file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_BINARY_DIR}/far.7z DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/farmanager)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/farmanager/PluginSDK/Headers.c/plugin.hpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/far-sdk/far)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/farmanager/PluginSDK/Headers.c/farcolor.hpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/far-sdk/far)

set(FAR_MANAGER_EXE ${CMAKE_CURRENT_BINARY_DIR}/farmanager/far.exe PARENT_SCOPE)
set(FAR_MANAGER_PLUGINS_DIR ${CMAKE_CURRENT_BINARY_DIR}/farmanager/Plugins PARENT_SCOPE)

add_library(far INTERFACE)
target_include_directories(far INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/far-sdk)

