cmake_minimum_required(VERSION 2.8)
include(FindPackageHandleStandardArgs)
project(BulletWormTest)

set(BULLET_ROOT $ENV{BULLET_ROOT})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

if( MSVC )
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif( MSVC )

set(bullet3test BulletWormTest)

find_package(BULLET REQUIRED)

include_directories(${BULLET_INCLUDE_DIR})
set(SOURCES Main.cpp)

add_executable(${bullet3test} ${SOURCES})

target_link_libraries(${bullet3test} debug ${BULLET_DYNAMICS_LIBRARY_DEBUG})
target_link_libraries(${bullet3test} optimized ${BULLET_DYNAMICS_LIBRARY})

target_link_libraries(${bullet3test} debug ${BULLET_COLLISION_LIBRARY_DEBUG})
target_link_libraries(${bullet3test} optimized ${BULLET_COLLISION_LIBRARY})

target_link_libraries(${bullet3test} debug ${BULLET_MATH_LIBRARY_DEBUG}) 
target_link_libraries(${bullet3test} optimized ${BULLET_MATH_LIBRARY}) 
