# Try to find GLEW. Once done, this will define:
#
#   GLEW_FOUND - variable which returns the result of the search
#   GLEW_INCLUDE_DIRS - list of include directories
#   GLEW_LIBRARIES - options for the linker

if(APPLE)
	find_package(PkgConfig)
	pkg_check_modules(PC_GLEW QUIET glew)
endif(APPLE)


find_path(GLEW_INCLUDE_DIR
	GL/glew.h
	HINTS 
		${PC_GLEW_INCLUDEDIR}
		${PC_GLEW_INCLUDE_DIRS}
		${GLEW_ROOT}/include
)
find_library(GLEW_LIBRARY
	GLEW glew32s glew32sd
	HINTS
		${PC_GLEW_LIBDIR}
		${PC_GLEW_LIBRARY_DIRS}
		${GLEW_ROOT}/lib/msvc64/Release
		${GLEW_ROOT}/lib/msvc64/Debug
)

set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
set(GLEW_LIBRARIES ${GLEW_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG
	GLEW_INCLUDE_DIR
	GLEW_LIBRARY
)

mark_as_advanced(
	GLEW_INCLUDE_DIR
	GLEW_LIBRARY
)
