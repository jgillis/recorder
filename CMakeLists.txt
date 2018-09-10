cmake_minimum_required (VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(Recorder)

add_library(recorder recorder.hpp recorder.cpp)
add_executable(test test.cpp)
target_link_libraries(test recorder)

install(TARGETS test DESTINATION bin)
