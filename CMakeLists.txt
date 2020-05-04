cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-dependencies)
set(Irrlicht_FIND_REQUIRED)

include(${CMAKE_MODULE_PATH}/FindIrrlicht.cmake)

file(
        GLOB_RECURSE
        SOURCES_CPP
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)
file(
        GLOB_RECURSE
        SOURCES_HPP
        ${PROJECT_SOURCE_DIR}/include/*.hpp
)

add_executable(bomberman ${SOURCES_CPP} ${SOURCES_HPP})

target_include_directories(bomberman PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${Irrlicht_INCLUDE_DIRS}
        )

target_link_libraries(bomberman
        ${Irrlicht_LIBRARIES}
        )

if (UNIX)
    target_link_libraries(bomberman GL Xxf86vm Xext X11 Xcursor)
endif (UNIX)

target_compile_features(bomberman PRIVATE cxx_std_11)