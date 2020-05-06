cmake_minimum_required(VERSION 3.11)

set(CMAKE_PROJECT_NAME bomberman) 

project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-dependencies)

if(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W4")
endif(MSVC)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif(NOT MSVC)

if (NOT APPLE)
    set(Irrlicht_FIND_REQUIRED)

    include(${CMAKE_MODULE_PATH}/FindIrrlicht.cmake)
    include(${CMAKE_MODULE_PATH}/FindSFML.cmake)
endif(NOT APPLE)

if (APPLE)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR})

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    include_directories(include)
    include_directories("${CMAKE_MODULE_PATH}/include")

    link_directories(/usr/local/lib)
    include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

    
endif(APPLE)

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

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_HPP})

if(MSVC)
	set(BIN_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${PROJECT_SOURCE_DIR}/cmake-dependencies/Irrlicht.dll"
	        "${BIN_DIRECTORY}/Irrlicht.dll")
    set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY} )
    set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIRECTORY} )
    set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIRECTORY} )
endif(MSVC)

if (NOT APPLE)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${Irrlicht_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
    )

    target_link_libraries(${CMAKE_PROJECT_NAME}
        ${Irrlicht_LIBRARIES}
        ${SFML_LIBRARIES}
    )
    
    target_link_libraries(${CMAKE_PROJECT_NAME} uuid)
endif (NOT APPLE)

if (LINUX)
	target_link_libraries(${CMAKE_PROJECT_NAME} GL Xxf86vm Xext X11 Xcursor)
endif (LINUX)

if (APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME} Irrlicht)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${COREFOUNDATION_FRAMEWORK} ${IOKIT_FRAMEWORK})
endif(APPLE)
