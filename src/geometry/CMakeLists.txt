### geometry is a header-only library

project(CMTL_geometry)

### Register all sources
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PRIVATE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})