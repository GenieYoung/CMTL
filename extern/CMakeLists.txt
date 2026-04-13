project(CMTL_External)

add_library(${PROJECT_NAME} INTERFACE)

option(CMTL_LINK_CORE "Link CORE library" ON)

# GMP and GMPXX
find_package(GMP)
find_package(GMPXX)
if(GMP_FOUND AND GMPXX_FOUND)
	target_include_directories(${PROJECT_NAME} INTERFACE
		${GMP_INCLUDES}
		${GMPXX_INCLUDES}
	)
	target_link_libraries(${PROJECT_NAME} INTERFACE
		${GMP_LIBRARIES}
		${GMPXX_LIBRARIES}
	)
	target_compile_definitions(${PROJECT_NAME} INTERFACE USE_GMP)
else()
	message(WARNING "GMP not found.")
endif()

# MPFR
find_package(MPFR)
if(MPFR_FOUND)
	target_include_directories(${PROJECT_NAME} INTERFACE
		${MPFR_INCLUDES}
	)
	target_link_libraries(${PROJECT_NAME} INTERFACE
		${MPFR_LIBRARIES}
	)
    target_compile_definitions(${PROJECT_NAME} INTERFACE USE_MPFR)
else()
	message(WARNING "MPFR not found.")
endif()

# CORE
if(CMTL_LINK_CORE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CORE)
    if(TARGET CORE)
        target_link_libraries(${PROJECT_NAME} INTERFACE CORE)
        target_compile_definitions(${PROJECT_NAME} INTERFACE USE_CORE)
    else()
        message(WARNING "Link CORE Failed.")
    endif()
endif()