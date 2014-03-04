cmake_minimum_required(VERSION 2.8)
include(FindPackageHandleStandardArgs)
project(CreatureEvolution)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

set(ctEvo CreatureEvolution)
# set path to custom find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Bullet is a completely external library, not included in the source control
# (because of size) this is generally only required for Windows, OSX finds it automagically

#NOTE: this is probably stupid (non-general)
if(MSVC)
  set(BULLET_ROOT $ENV{BULLET_ROOT})
endif(MSVC)

if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif(MSVC)

# find FreeGLUT, BULLET, GLEW for OSX and Windows
find_package(BULLET REQUIRED)
find_package(OPENGL REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(SFGUI REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${SFGUI_INCLUDE_DIR})

# If you want your own include/ directory, set this, and then you can do
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src/include)
include_directories(${COMMON_INCLUDES})

# source code is here
add_subdirectory(src)

# treat main separatly, all other functionality will be built into a library
# for testing purposes
set(MAIN "src/Main.cpp")

# link main file to executable
add_executable(${ctEvo} ${MAIN})

set_target_properties(CreatureEvolution_lib PROPERTIES COMPILE_FLAGS "-std=c++11")
set_target_properties(${ctEvo} PROPERTIES COMPILE_FLAGS "-std=c++11")

# this is defined in the sub directory src/
target_link_libraries(${ctEvo} CreatureEvolution_lib)

# Linking Bullet. NOTE: For now, no debug libraries
target_link_libraries(${sfguihw} ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})


# Linking OpenGL, SFML, SFGui
target_link_libraries(${sfguihw} ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${OPENGL_LIBRARIES})

######### OPENGL LIBRARY (ONLY FOR OSX) #############
if(APPLE)
  target_link_libraries(${ctEvo} ${OPENGL_FRAMEWORK} ${COCOA_FRAMEWORK})
endif(APPLE)
####################################

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
  add_executable(runUnitTests test/CreatureTest.cpp test/ChromosomeTest.cpp)
  set_target_properties(runUnitTests PROPERTIES COMPILE_FLAGS "-std=gnu++11")

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  target_link_libraries(runUnitTests CreatureEvolution_lib)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND runUnitTests)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made runUnitTests)
endif()
