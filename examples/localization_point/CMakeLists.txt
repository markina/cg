cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(localization-point)

add_executable(localization-point localization_point_viewer.cpp)
target_link_libraries(localization-point visualization ${GMP_LIBRARIES})
