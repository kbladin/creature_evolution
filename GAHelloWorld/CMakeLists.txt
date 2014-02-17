# project(GAHelloWorld)
# cmake_minimum_required(VERSION 2.8)
# file(GLOB_RECURSE SRC *.cpp)
# add_executable(${PROJECT_NAME} ${SRC})

cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME GAHelloWorld)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g")

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

################################
# Normal Libraries & Executables
################################
file(GLOB Library_SOURCES src/AutoInitRNG.cpp src/Chromosome.cpp 
		src/Population.cpp)
file(GLOB Library_HEADERS src/AutoInitRNG.h src/Chromosome.h src/Population.h)
add_library(GAHelloWorld_lib ${Library_SOURCES} ${Library_HEADERS})
add_executable(GAHelloWorld src/GAHelloWorld.cpp)
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere.
set_target_properties(GAHelloWorld_lib PROPERTIES COMPILE_FLAGS "-std=c++11")
set_target_properties(GAHelloWorld PROPERTIES COMPILE_FLAGS "-std=c++11")

target_link_libraries(GAHelloWorld GAHelloWorld_lib)
################################
# Testing
################################
if (test)
	
  if( MSVC ) 
    # VS2012 doesn't support correctly the tuples yet
    add_definitions( /D _VARIADIC_MAX=10 )
  endif( MSVC)

  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/gtest-1.7.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(runUnitTests test/GA_ChromosomeTest.cpp 
  				test/GA_PopulationTest.cpp)
  set_target_properties(runUnitTests PROPERTIES COMPILE_FLAGS "-std=gnu++11")

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  target_link_libraries(runUnitTests GAHelloWorld_lib)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND runUnitTests)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made runUnitTests)
endif()
