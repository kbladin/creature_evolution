cmake_minimum_required(VERSION 2.8.12)
include(FindPackageHandleStandardArgs)
project(CreatureEvolution)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

set(ctEvo CreatureEvolution)
# set path to custom find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)


if(WIN32)
	set(CMAKE_PREFIX_PATH $ENV{WINSDK} ${CMAKE_PREFIX_PATH})
endif(WIN32)

# define Qt path for Windows and OS
if(WIN32 OR APPLE)
	if (DEFINED ENV{QTDIR})
	    set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})
	else ()
	    message (FATAL_ERROR "ERROR: Environment variable QTDIR is not set. Please locate your Qt folder MY_QT5_DIR.")
	endif()
endif(WIN32 OR APPLE)

#NOTE: this is probably stupid (non-general)
if(MSVC)
  set(BULLET_ROOT ${CMAKE_SOURCE_DIR}/external_libs/bullet)
  set(GLEW_ROOT ${CMAKE_SOURCE_DIR}/external_libs/glew)
endif(MSVC)

MESSAGE( STATUS "Bullet dir: " ${BULLET_ROOT} )


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)



# find FreeGLUT, BULLET, GLEW for OSX and Windows
find_package(BULLET REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)


#static please!
if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif(MSVC)


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/external_libs/glm)




#Linux magic
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  #Set additional libs for GLFW on Linux
  set( ADDITIONAL_LIBS 
      -pthread
      -lrt
      -lXinerama
      -lXrandr
      -lXxf86vm
      -lXi
      -lX11
     )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")








# If you want your own include/ directory, set this, and then you can do
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src/include )
include_directories(${COMMON_INCLUDES})

# source code is here
add_subdirectory(src)

# treat main separatly, all other functionality will be built into a library
# for testing purposes
set(MAIN "src/Main.cpp")

# link main file to executable
add_executable(${ctEvo} ${MAIN})

#for osx and linux
if(UNIX)
  set_target_properties(CreatureEvolution_lib PROPERTIES COMPILE_FLAGS "-std=c++11")
  set_target_properties(${ctEvo} PROPERTIES COMPILE_FLAGS "-std=c++11")
endif(UNIX)

target_link_libraries(${ctEvo} ${OPENGL_LIBRARIES}  ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY})

# this is defined in the sub directory src/
target_link_libraries(${ctEvo} CreatureEvolution_lib)

# Linking OpenGL etc
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(${ctEvo} ${X11_LIBRARIES} ${ADDITIONAL_LIBS})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Linking Bullet. NOTE: For now, no debug libraries
target_link_libraries(${ctEvo} ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})


######### OPENGL LIBRARY (ONLY FOR OSX) #############
if(APPLE)
  target_link_libraries(${ctEvo} ${OPENGL_FRAMEWORK} ${COCOA_FRAMEWORK})
endif(APPLE)
####################################

qt5_use_modules(${ctEvo} Widgets Core Gui OpenGL)




################################
# Testing
################################
if (test)
	
  if( MSVC ) 
    # VS2012 doesn't support correctly the tuples yet
    add_definitions( /D _VARIADIC_MAX=10 )
  endif( MSVC)

  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(external_libs/gtest-1.7.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(runUnitTests test/CreatureTest.cpp 
    test/ChromosomeTest.cpp test/SceneManagerTest.cpp test/ShapeTest.cpp
    test/NodeTest.cpp)
  set_target_properties(runUnitTests PROPERTIES COMPILE_FLAGS "-std=gnu++11")

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  target_link_libraries(runUnitTests CreatureEvolution_lib)
  target_link_libraries(runUnitTests ${OPENGL_LIBRARIES}  ${OPENGL_glu_LIBRARY}  
    ${GLEW_LIBRARY} ${BULLET_DYNAMICS_LIBRARY} 
    ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND runUnitTests)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made runUnitTests)
endif()
