project(CMTL)

### Find dependencies
find_package(GMP)
find_package(GMPXX)

### geometry is a header-only library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CMTL)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PRIVATE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(GMP_FOUND AND GMPXX_FOUND)
    target_link_libraries(${PROJECT_NAME} INTERFACE
        ${GMP_LIBRARIES}
        ${GMPXX_LIBRARIES}
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE USE_GMP)
else()
    message("GMP not found.")
endif()

target_link_libraries(${PROJECT_NAME} INTERFACE
    CMTL_Core
)

