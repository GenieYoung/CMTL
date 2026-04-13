project(CMTL_Core)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PRIVATE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CMTL_Core INTERFACE
    CMTL_External
)

