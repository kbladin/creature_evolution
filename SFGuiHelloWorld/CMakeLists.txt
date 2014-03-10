cmake_minimum_required( VERSION 2.8 )

project(SfGuiHelloWorld)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

set(sfguihw SfGuiHelloWorld)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Compilier flags
if(MSVC)
	# NOTE: This might be really stupid (but so is MSVC :)
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
else(MSVC)
	# C++11 support required for SFML and SFGui
	# set(CMAKE_CXX_FLAGS "-std=c++11")
endif(MSVC)

find_package(BULLET REQUIRED)
find_package(OPENGL REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(SFGUI REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${SFGUI_INCLUDE_DIR})

# Source code
add_subdirectory(src)

# Separating out MAIN in order to build rest of the project as a library
set(MAIN "src/Main.cpp")
add_executable(${sfguihw} ${MAIN})

set_target_properties(sfguihw_lib PROPERTIES COMPILE_FLAGS "-std=c++11")
set_target_properties(${sfguihw} PROPERTIES COMPILE_FLAGS "-std=c++11")

# Linking project library
target_link_libraries(${sfguihw} sfguihw_lib)

# Linking Bullet. NOTE: For now, no debug libraries
target_link_libraries(${sfguihw} ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})


# Linking OpenGL, SFML, SFGui
target_link_libraries(${sfguihw} ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${OPENGL_LIBRARIES})


# Setup and link Google Test
if(test)
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
	add_subdirectory(test)
	add_executable(runUnitTests "test/Dummy_test.cpp")
	set_target_properties(runUnitTests PROPERTIES COMPILE_FLAGS "-std=gnu++11")

	# Standard linking to gtest stuff.
	target_link_libraries(runUnitTests gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(runUnitTests sfguihw_lib)



	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable runUnitTests to see those specific tests.
	add_test(NAME that-test-I-made COMMAND runUnitTests)

	# You can also omit NAME and COMMAND. The second argument could be some other
	# test executable.
	add_test(that-other-test-I-made runUnitTests)
endif()
