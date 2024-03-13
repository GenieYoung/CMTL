project(test)

file(GLOB TEST_LIST "*.cpp")

foreach(test_file ${TEST_LIST})
    get_filename_component(test ${test_file} NAME)
    get_filename_component(exec ${test_file} NAME_WLE)
    add_executable(${exec} ${test})
    target_link_libraries(${exec} PRIVATE geometry)
endforeach()
