project(geometry)

### Find dependencies
#find_package(GMP REQUIRED)
#find_package(GMPXX REQUIRED)

file(GLOB_RECURSE SOURCE_LIST "*.cpp")

### Register all sources
add_library(${PROJECT_NAME} ${SOURCE_LIST})

### Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

### Link with dependencies
target_link_libraries(${PROJECT_NAME}
    ${GMP_LIBRARIES}
    ${GMPXX_LIBRARIES}
)