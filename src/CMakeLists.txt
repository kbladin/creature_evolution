file(GLOB SOURCES *.cpp)
file(GLOB HEADERS include/*.h)
file(GLOB to_remove Main.cpp)

list(REMOVE_ITEM SOURCES ${to_remove})


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Quick)
find_package(Qt5Gui)

add_library(CreatureEvolution_lib ${SOURCES} ${HEADERS})

qt5_use_modules(CreatureEvolution_lib Core Gui Quick)