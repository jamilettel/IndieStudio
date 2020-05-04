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

if(MSVC)
	set(BIN_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
	add_custom_command(TARGET bomberman POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${PROJECT_SOURCE_DIR}/cmake-dependencies/Irrlicht.dll"
	        "${BIN_DIRECTORY}/Irrlicht.dll")
    set_target_properties( bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY} )
    set_target_properties( bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIRECTORY} )
    set_target_properties( bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIRECTORY} )

endif(MSVC)

target_include_directories(bomberman PUBLIC
		${PROJECT_SOURCE_DIR}/include
		${Irrlicht_INCLUDE_DIRS}
)

target_link_libraries(bomberman
		${Irrlicht_LIBRARIES}
)

# target_link_libraries(bomberman Irrlicht)
# # target_link_libraries(bomberman Xxf86vm)
# # target_link_libraries(bomberman Xext)
# # target_link_libraries(bomberman X11)
# target_link_libraries(bomberman IrrKlang)
# target_link_libraries(bomberman IkpFlac)
# target_link_libraries(bomberman IkpMP3)

if (UNIX)
	target_link_libraries(bomberman GL Xxf86vm Xext X11 Xcursor)
endif (UNIX)
target_compile_features(bomberman PRIVATE cxx_std_17)
