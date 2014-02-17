cmake_minimum_required(VERSION 2.8)
include(FindPackageHandleStandardArgs)
project(BulletHelloWorld)

set(BULLET_ROOT $ENV{BULLET_ROOT})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)


set(bullet3test BulletHelloWorld)

find_package(BULLET REQUIRED)

include_directories(${BULLET_INCLUDE_DIR})
set(SOURCES Main.cpp)

add_executable(${bullet3test} ${SOURCES})

target_link_libraries(${bullet3test} ${BULLET_DYNAMICS_LIBRARY})
target_link_libraries(${bullet3test} ${BULLET_COLLISION_LIBRARY})
target_link_libraries(${bullet3test} ${BULLET_MATH_LIBRARY}) 