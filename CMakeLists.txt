cmake_minimum_required(VERSION 3.11)
project(bomberman)

add_library(bomberman src/main.cpp)

target_compile_features(bomberman PRIVATE cxx_std_11)
