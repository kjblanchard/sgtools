cmake_minimum_required(VERSION 3.10)
set(LIBRARY_NAME sgtools)
option(SGTOOLS_INSTALL_LIB "Install sgforge library" ON)
project(${LIBRARY_NAME} C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_MESSAGE LAZY)
if(UNIX OR APPLE)
    list(APPEND COMPILE_OPTIONS -Wall -Wextra -Wdeprecated -Wno-unused-parameter -Wno-sign-compare -Wshadow -Wnull-dereference -Wdouble-promotion -Wformat=2)
endif(UNIX OR APPLE)
add_library(${LIBRARY_NAME} STATIC 
    ./src/tools.c
    ./src/log.c
)
target_include_directories(${LIBRARY_NAME} PRIVATE ./include)
if(SGFORGE_INSTALL_LIB)
    install(TARGETS ${LIBRARY_NAME} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
    install(DIRECTORY ./include/ DESTINATION include)
endif()
