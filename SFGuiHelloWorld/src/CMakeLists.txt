add_subdirectory(include)

file(GLOB SOURCES *.cpp)
file(GLOB to_remove Main.cpp)

list(REMOVE_ITEM SOURCES ${to_remove})

add_library(sfguihw_lib ${SOURCES} ${HEADERS})