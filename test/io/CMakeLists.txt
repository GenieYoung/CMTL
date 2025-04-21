project(io_test)

file(GLOB_RECURSE TEST_LIST "*.cpp")

foreach(test_file ${TEST_LIST})
    #get_filename_component(test ${test_file} NAME)
    #file(RELATIVE_PATH test ${CMAKE_CURRENT_SOURCE_DIR} ${test_file})
    get_filename_component(exec ${test_file} NAME_WE)
    add_executable(${exec} ${test_file})
    target_link_libraries(${exec} PRIVATE CMTL)
endforeach()
