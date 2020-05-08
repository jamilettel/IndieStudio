cmake_minimum_required(VERSION 3.11)

set(CMAKE_PROJECT_NAME bomberman) 

project(${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH cmake-dependencies)

add_definitions(-DRESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources/")

if(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W4")
else(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif(MSVC)

if (NOT APPLE)
    if(NOT CMAKE_CL_64)
        include(${CMAKE_MODULE_PATH}/win32/FindIrrlicht.cmake)
        include(${CMAKE_MODULE_PATH}/win32/FindSFML.cmake)
    else(NOT CMAKE_CL_64)
        include(${CMAKE_MODULE_PATH}/win64/FindIrrlicht.cmake)
        include(${CMAKE_MODULE_PATH}/win64/FindSFML.cmake)
    endif()
else (NOT APPLE)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR})

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    include_directories(include)
    include_directories(/usr/local/include)
    include_directories("${CMAKE_MODULE_PATH}/include")
    include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

    link_directories(/usr/local/lib)
endif (NOT APPLE)

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

if (APPLE)
    add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE ${SOURCES_CPP} ${SOURCES_HPP})
else (APPLE)
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES_CPP})
endif (APPLE)

# if(MSVC)
# 	set(BIN_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
# 	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E copy_if_different
# 			"cmake-dependencies/Irrlicht.dll"
# 	        "${BIN_DIRECTORY}/Irrlicht.dll")
#     set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY} )
#     set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIRECTORY} )
#     set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIRECTORY} )
# endif(MSVC)

if (NOT APPLE)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
            include
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
    target_link_libraries(${CMAKE_PROJECT_NAME} Irrlicht sfml-audio)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SFML_LIBRARIES})

    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${COREFOUNDATION_FRAMEWORK} ${IOKIT_FRAMEWORK})
endif(APPLE)