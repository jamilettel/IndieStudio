cmake_minimum_required(VERSION 3.11)
project(bomberman)

include(FindIrrlicht.cmake)
include_directories(${Irrlicht_INCLUDE_DIRS})

add_executable(bomberman src/main.cpp)

target_link_libraries(bomberman Irrlicht)
target_link_libraries(bomberman GL)
target_link_libraries(bomberman Xxf86vm)
target_link_libraries(bomberman Xext)
target_link_libraries(bomberman X11)

target_compile_features(bomberman PRIVATE cxx_std_11)