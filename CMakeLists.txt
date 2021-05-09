cmake_minimum_required (VERSION 3.6)
project(templatebot)
aux_source_directory("src" coresrc)
add_executable(templatebot ${coresrc})

string(ASCII 27 Esc)

include_directories( "include" )

target_link_libraries(templatebot dl dpp crypto ssl fmtd)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -g -fPIC -rdynamic")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

target_link_libraries(templatebot)

