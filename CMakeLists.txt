cmake_minimum_required(VERSION 3.0)

project(CMTL)

set(CMAKE_BUILD_TYPE Debug)

option(LIBASAN_OPTION "libasan option" ON)
if (LIBASAN_OPTION)
    message("libasan option is on.")
    set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer")
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(test)

