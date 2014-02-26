cmake_minimum_required(VERSION 2.8)
include(FindPackageHandleStandardArgs)
project(BulletWorm)

set(btWorm BulletWorm)

# Bullet is a completely external library, not included in the source control
# (because of size) this is generally only required for Windows, OSX finds it # automagically
set(BULLET_ROOT $ENV{BULLET_ROOT})

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif(MSVC)

# freeglut and glew are included in source control
# set(FREEGLUT_ROOT "../libs/freeglut")
# set(GLEW_ROOT "../libs/glew")

# set path to custom find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# find FreeGLUT, BULLET, GLEW for OSX and Windows
find_package(BULLET REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${BULLET_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

# source code is here
add_subdirectory(src)

# treat main separatly, all other functionality will be built into a library
# for testing purposes
set(MAIN "src/Main.cpp")

# link main file to executable
add_executable(${btWorm} ${MAIN})

# this is defined in the sub directory src/
target_link_libraries(${btWorm} BulletWorm_lib)


######### BULLET LIBRARIES #########
	if(APPLE)
		target_link_libraries(${btWorm} optimized ${BULLET_DYNAMICS_LIBRARY})
		target_link_libraries(${btWorm} optimized ${BULLET_COLLISION_LIBRARY})
		target_link_libraries(${btWorm} optimized ${BULLET_MATH_LIBRARY}) 
	endif(APPLE)

	if(WIN32)
		target_link_libraries(${btWorm} debug ${BULLET_DYNAMICS_LIBRARY_DEBUG})
		target_link_libraries(${btWorm} optimized ${BULLET_DYNAMICS_LIBRARY})
		target_link_libraries(${btWorm} debug ${BULLET_COLLISION_LIBRARY_DEBUG})
		target_link_libraries(${btWorm} optimized ${BULLET_COLLISION_LIBRARY})
		target_link_libraries(${btWorm} debug ${BULLET_MATH_LIBRARY_DEBUG})
		target_link_libraries(${btWorm} optimized ${BULLET_MATH_LIBRARY}) 
	endif(WIN32)
####################################


######### FREEGLUT LIBRARY #########
	if(APPLE)
		target_link_libraries(${btWorm} optimized ${GLUT_LIBRARIES}) 
	endif(APPLE)
	if(WIN32)
		target_link_libraries(${btWorm} optimized ${GLUT_LIBRARIES}) 
		# target_link_libraries(${btWorm} debug ${FREEGLUT_LIBRARY_DEBUG}) 
	endif(WIN32)
####################################

######### GLEW LIBRARY #############
	target_link_libraries(${btWorm} ${GLEW_LIBRARIES})
####################################

# TODO:
# 1. post-build scripts to move dll/binaries to output folders for MSVC
# and OSX