# - Find AlSoft
# Find the native AlSoft includes and libraries
#
#  ALSOFT_INCLUDE_DIR - include files for AlSoft
#  ALSOFT_LIBRARIES   - List of libraries when using libAlSoft.
#  ALSOFT_FOUND       - True if libAlSoft found.

if(ALSOFT_INCLUDE_DIR)
    # Already in cache, be silent
    set(ALSOFT_FIND_QUIETLY TRUE)
endif(ALSOFT_INCLUDE_DIR)

find_path(ALSOFT_INCLUDE_DIR AL/al.h)
find_library(ALSOFT_LIBRARY NAMES openal OpenAL32.dll)

# Handle the QUIETLY and REQUIRED arguments and set ALSOFT_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AlSoft DEFAULT_MSG ALSOFT_LIBRARY ALSOFT_INCLUDE_DIR)

if(ALSOFT_FOUND)
  set(ALSOFT_LIBRARIES ${ALSOFT_LIBRARY})
else(ALSOFT_FOUND)
  set(ALSOFT_LIBRARIES)
endif(ALSOFT_FOUND)

mark_as_advanced(ALSOFT_INCLUDE_DIR ALSOFT_LIBRARY)