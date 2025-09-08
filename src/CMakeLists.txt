project(CMTL)

### Find dependencies
find_package(GMP REQUIRED)
find_package(GMPXX REQUIRED)

### geometry is a header-only library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CMTL)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PRIVATE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(GMP_FOUND)
    target_link_libraries(${PROJECT_NAME} INTERFACE
        ${GMP_LIBRARIES}
        ${GMPXX_LIBRARIES}
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE USE_GMP)
endif()

target_link_libraries(${PROJECT_NAME} INTERFACE
    ${GMP_LIBRARIES}
    ${GMPXX_LIBRARIES}
    CMTL_Core
)

