cmake_minimum_required(VERSION 2.6)

# List of libraries
set(LIBRARIES)
set(EXTERN_LIBRARIES lsfml-system lsfml-network)
set(EXTERN_LINK_DIRECTORIES /usr/lib64/)
set(EXTERN_INCLUDE_DIRECTORIES /usr/include/SFML)


# DO NOT TOUCH

set(MY_PROJECT_NAME "p2pserver")

project(${MY_PROJECT_NAME} CXX)

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Werror -std=c++0x -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Werror -std=c++0x -pedantic -g")
set(LINK_FLAGS_RELEASE "-Wall -Wextra -Werror -std=c++0x -pedantic")
set(LINK_FLAGS_DEBUG "-Wall -Wextra -Werror -std=c++0x -pedantic -g")

# Compilation of the lib
foreach(f ${LIBRARIES})
    set(MY_LIBRARY_NAME ${f})
    file(GLOB_RECURSE FILES libs/${f}/*)
    project(${MY_PROJECT_NAME} CXX)
    add_library(${MY_LIBRARY_NAME} STATIC ${FILES})
    target_link_libraries(${MY_LIBRARY_NAME} ${${f}})
endforeach(f)

# Compilation of the program
file(GLOB_RECURSE FILES src/*)
foreach(f ${LIBRARIES} variables)
    include_directories(${PROJECT_SOURCE_DIR}/${f})
endforeach(f)

include_directories(${PROJECT_BINARY_DIR}/src/libs/ ${EXTERN_INCLUDE_DIRECTORIES})
link_directories(${PROJECT_BINARY_DIR}/src/libs/ ${EXTERN_LINK_DIRECTORIES})
add_executable(../${MY_PROJECT_NAME} ${FILES})
target_link_libraries(../${MY_PROJECT_NAME} ${LIBRARIES} ${EXTERN_LIBRARIES})
