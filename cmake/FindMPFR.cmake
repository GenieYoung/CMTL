# Try to find the MPFR library
# MPFR_FOUND - system has MPFR
# MPFR_INCLUDES - the MPFR include directory
# MPFR_LIBRARIES - libraries needed to use MPFR

# MPFR needs gmp
if(GMP_FOUND AND GMPXX_FOUND)
    if (MPFR_INCLUDES AND MPFR_LIBRARIES)
    set(MPFR_FIND_QUIETLY TRUE)
    endif (MPFR_INCLUDES AND MPFR_LIBRARIES)

    find_path(MPFR_INCLUDES
    NAMES mpfr.h
    PATHS
    $ENV{MPFRDIR}
    ${INCLUDE_INSTALL_DIR}
    )

    find_library(MPFR_LIBRARIES
    NAMES mpfr
    PATHS
    $ENV{MPFRDIR}
    ${LIB_INSTALL_DIR}
    )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(MPFR DEFAULT_MSG
                                    MPFR_INCLUDES MPFR_LIBRARIES)

    mark_as_advanced(MPFR_INCLUDES MPFR_LIBRARIES)
endif()
