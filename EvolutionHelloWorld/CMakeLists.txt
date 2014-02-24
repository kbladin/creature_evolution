# project(HelloWorld)
# cmake_minimum_required(VERSION 2.8)
# file(GLOB_RECURSE SRC *.cpp)
# add_executable(${PROJECT_NAME} ${SRC})

cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME HelloWorld)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g")

# If you want your own include/ directory, set this, and then you can do
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

################################
# Normal Libraries & Executables
################################
file(GLOB Library_SOURCES src/AutoInitRNG.cpp src/Evolution.cpp 
		src/Creature.cpp)
file(GLOB Library_HEADERS include/AutoInitRNG.h include/Evolution.h include/Creature.h)
add_library(HelloWorld_lib ${Library_SOURCES} ${Library_HEADERS})
add_executable(HelloWorld src/HelloWorld.cpp)
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere.
set_target_properties(HelloWorld_lib PROPERTIES COMPILE_FLAGS "-std=c++11")
set_target_properties(HelloWorld PROPERTIES COMPILE_FLAGS "-std=c++11")

target_link_libraries(HelloWorld HelloWorld_lib)