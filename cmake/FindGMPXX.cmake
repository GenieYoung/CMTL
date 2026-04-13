# Try to find the GMPXX libraries
# GMPXX_FOUND - system has GMPXX lib
# GMPXX_INCLUDES - the GMPXX include directory
# GMPXX_LIBRARIES - Libraries needed to use GMPXX

# GMPXX needs GMP
if(GMP_FOUND)
  if (GMPXX_INCLUDES AND GMPXX_LIBRARIES)
    set(GMPXX_FIND_QUIETLY TRUE)
  endif()

  find_path(GMPXX_INCLUDES 
    NAMES gmpxx.h
    PATHS 
    $ENV{GMPXXDIR}
    ${LIB_INSTALL_DIR}
  )

  find_library(GMPXX_LIBRARIES
    NAMES gmpxx
    PATHS
    $ENV{GMPXXDIR}
    ${LIB_INSTALL_DIR}
  )

  include(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMPXX
                          REQUIRED_VARS GMPXX_LIBRARIES GMPXX_INCLUDES
                          VERSION_VAR GMPXX_VERSION_STRING)

  mark_as_advanced(GMPXX_INCLUDES GMPXX_LIBRARIES)

endif()
