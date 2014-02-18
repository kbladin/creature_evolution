cmake_minimum_required(VERSION 2.8.11)

if(WIN32)
	if(MSVC)
		set (CMAKE_PREFIX_PATH $ENV{QT5_MSVC})
	else(MSVC)
		set (CMAKE_PREFIX_PATH $ENV{QT5_MINGW})
	endif(MSVC)
	
	set (CMAKE_LIBRARY_PATH "C:\\Program Files (x86)\\Windows Kits\\8.0\\Lib\\win8\\um\\x64") 
endif(WIN32)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
if( WIN32 )
	add_executable(helloworld WIN32 Main.cpp)
else( WIN32 )
	add_executable(helloworld Main.cpp)
endif( WIN32 )


# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)