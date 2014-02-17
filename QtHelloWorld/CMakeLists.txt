cmake_minimum_required(VERSION 2.8.9)
if(MSVC)
	set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.2.1\\5.2.1\\msvc2012_64_opengl\\")
endif(MSVC)

set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.2.1_MinGW\\5.2.1\\mingw48_32")
project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
if(WIN32)
	add_executable(helloworld WIN32 Main.cpp)
endif(WIN32)

target_link_libraries(helloworld Qt5::Widgets Qt5::WinMain)
# Use the Widgets module from Qt 5.
qt5_use_modules(helloworld Widgets)