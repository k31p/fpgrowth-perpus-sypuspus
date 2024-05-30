cmake_minimum_required(VERSION 3.5)
project(teamthirteen_fpgrowth VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES
    internal/*.hpp
    external/*.hpp
)

link_libraries(
    ncurses
)
add_executable(${PROJECT_NAME} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
