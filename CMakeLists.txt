cmake_minimum_required(VERSION 3.13)

project(test_tbb)

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(test_tbb main.cpp)

target_link_libraries(test_tbb tbb)

