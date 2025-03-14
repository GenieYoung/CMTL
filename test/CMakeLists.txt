project(test)

find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geo2d)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geo3d)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geometry_algorithm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/io)