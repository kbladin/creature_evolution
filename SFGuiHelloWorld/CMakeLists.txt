cmake_minimum_required( VERSION 2.8 )

project(SfGuiHelloWorld)

set(sfguihw SfGuiHelloWorld)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Compilier flags
if(MSVC)
	# NOTE: This might be really stupid (but so is MSVC :)
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
else(MSVC)
	# C++11 support required for SFML and SFGui
	set(CMAKE_CXX_FLAGS "-std=c++11")
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

# Linking project library
# target_link_libraries(${sfguihw} sfguihw_lib)

# Linking Bullet. NOTE: For now, no debug libraries
target_link_libraries(${sfguihw} ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${BULLET_MATH_LIBRARY})


# Linking OpenGL, SFML, SFGui
target_link_libraries(${sfguihw} ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${OPENGL_LIBRARIES})