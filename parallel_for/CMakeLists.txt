cmake_minimum_required(VERSION 3.13)

project(test_parfor)

link_directories(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(test_parfor parfor.cpp)

target_link_libraries(test_parfor tbb)

