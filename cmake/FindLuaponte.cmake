# Locate Luaponte library
# This module defines
#  LUAPONTE_FOUND, if false, do not try to link to Luaponte
#  LUAPONTE_LIBRARIES
#  LUAPONTE_INCLUDE_DIR, where to find luaponte.hpp

FIND_PATH(LUAPONTE_INCLUDE_DIR luaponte.hpp
  HINTS
  $ENV{LUAPONTE_DIR}
  PATH_SUFFIXES luaponte include/luaponte include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /opt/local # DarwinPorts
  /opt
)

FIND_LIBRARY(LUAPONTE_LIBRARY
  NAMES luaponte
  HINTS
  $ENV{LUAPONTE_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /opt/local
  /opt
)


IF(LUAPONTE_LIBRARY)
    SET( LUAPONTE_LIBRARIES "${LUAPONTE_LIBRARY}" CACHE STRING "Luaponte Libraries")
ENDIF(LUAPONTE_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LUAPONTE_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Luaponte  DEFAULT_MSG  LUAPONTE_LIBRARIES LUAPONTE_INCLUDE_DIR)

IF( NOT LUAPONTE_FIND_QUIETLY )
    IF( LUAPONTE_FOUND )
        MESSAGE(STATUS "Found LuaPonte: ${LUAPONTE_LIBRARY}" )
    ENDIF()
ENDIF()

MARK_AS_ADVANCED(LUAPONTE_INCLUDE_DIR LUAPONTE_LIBRARIES LUAPONTE_LIBRARY LUAPONTE_LIBRARY_DBG) 