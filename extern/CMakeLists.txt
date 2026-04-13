project(CMTL_External)

add_library(${PROJECT_NAME} INTERFACE)

find_package(GMP)
find_package(GMPXX)
if(GMP_FOUND AND GMPXX_FOUND)
	target_include_directories(${PROJECT_NAME} INTERFACE
		${GMP_INCLUDES}
		${GMPXX_INCLUDE_DIRS}
	)
	target_link_libraries(${PROJECT_NAME} INTERFACE
		${GMP_LIBRARIES}
		${GMPXX_LIBRARIES}
	)
	target_compile_definitions(${PROJECT_NAME} INTERFACE USE_GMP)
else()
	message("GMP not found.")
endif()