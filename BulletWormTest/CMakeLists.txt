cmake_minimum_required(VERSION 2.8)
include(FindPackageHandleStandardArgs)
project(BulletWormTest)

set(BULLET_ROOT $ENV{BULLET_ROOT})
set(FREEGLUT_ROOT $ENV{FREEGLUT_ROOT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
# if( MSVC )
# 	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# endif( MSVC )

set(bullet3test BulletWormTest)

find_package(BULLET REQUIRED)
include_directories(${BULLET_INCLUDE_DIR})
find_package(FREEGLUT REQUIRED)
include_directories(${FREEGLUT_INCLUDE_DIR})
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

add_subdirectory(src)

set(MAIN "src/Main.cpp")

add_executable(${bullet3test} ${MAIN})
target_link_libraries(${bullet3test} BulletWorm_lib)

target_link_libraries(${bullet3test} debug ${BULLET_DYNAMICS_LIBRARY_DEBUG})
target_link_libraries(${bullet3test} optimized ${BULLET_DYNAMICS_LIBRARY})

target_link_libraries(${bullet3test} debug ${BULLET_COLLISION_LIBRARY_DEBUG})
target_link_libraries(${bullet3test} optimized ${BULLET_COLLISION_LIBRARY})

target_link_libraries(${bullet3test} debug ${BULLET_MATH_LIBRARY_DEBUG}) 
target_link_libraries(${bullet3test} optimized ${BULLET_MATH_LIBRARY}) 


target_link_libraries(${bullet3test} debug ${FREEGLUT_LIBRARY_DEBUG}) 
target_link_libraries(${bullet3test} optimized ${FREEGLUT_LIBRARY}) 

target_link_libraries(${bullet3test} ${GLEW_LIBRARY})