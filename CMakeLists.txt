cmake_minimum_required(VERSION 3.0)

project(CMTL)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(extern)
add_subdirectory(src/CMTL)
add_subdirectory(test)

