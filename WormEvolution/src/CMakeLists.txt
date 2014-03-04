add_subdirectory(include)
file(GLOB SOURCES *.cpp)
#file(GLOB HEADERS *.h)
file(GLOB to_remove Main.cpp)

list(REMOVE_ITEM SOURCES ${to_remove})

# if( MSVC )
# 	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# endif( MSVC )

add_library(CreatureEvolution_lib ${SOURCES} ${HEADERS})