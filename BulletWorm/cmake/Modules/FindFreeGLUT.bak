macro(_FIND_FREEGLUT_LIBRARY _var)
	find_library(${_var}
		NAMES
			${ARGN}
		HINTS
			if(WIN32)
				${FREEGLUT_ROOT}/lib/win/x64
			endif(WIN32)
			# if(APPLE)
			# 	${FREEGLUT_ROOT}/lib/osx/x64
			# endif(APPLE)
		PATH_SUFFIXES lib	
	)
	mark_as_advanced(${_var})
endmacro()

macro(_FREEGLUT_APPEND_LIBRARIES _list _release)
	set(_debug ${_release}_DEBUG)
	if(${_debug})
		set(${_list} ${${_list}} optimized ${${_release}} debug ${${_debug}})
   else()
      set(${_list} ${${_list}} ${${_release}})
   endif()
endmacro()

find_path(FREEGLUT_INCLUDE_DIR NAMES freeglut.h
	HINTS
		${FREEGLUT_ROOT}/include/GL
	PATH_SUFFIXES freeglut
)

if(WIN32)
	_FIND_FREEGLUT_LIBRARY(FREEGLUT_LIBRARY freeglut)
	_FIND_FREEGLUT_LIBRARY(FREEGLUT_LIBRARY_DEBUG freeglut_d)
endif(WIN32)
if(APPLE)
	_FIND_FREEGLUT_LIBRARY(FREEGLUT_LIBRARY libglut )
	_FIND_FREEGLUT_LIBRARY(FREEGLUT_LIBRARY_DEBUG libglut)
endif(APPLE)

# handle the QUIETLY and REQUIRED arguments and set BULLET_FOUND to TRUE if
# all listed variables are TRUE
#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FREEGLUT DEFAULT_MSG
	FREEGLUT_LIBRARY FREEGLUT_INCLUDE_DIR)

set(FREEGLUT_INCLUDE_DIRS ${FREEGLUT_INCLUDE_DIR})
if(FREEGLUT_FOUND)
   _FREEGLUT_APPEND_LIBRARIES(FREEGLUT_LIBRARIES FREEGLUT_LIBRARY)
endif()