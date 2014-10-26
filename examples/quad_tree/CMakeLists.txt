cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(quad-tree)

add_executable(quad-tree quad_tree_viewer.cpp)
target_link_libraries(quad-tree visualization ${GMP_LIBRARIES})
