cmake_minimum_required(VERSION 3.10)

project(refs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	link_directories(${CMAKE_SOURCE_DIR}/lib/x64/windows)
endif()

if(APPLE)
	find_package(SDL2 REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(ASSIMP REQUIRED)
	find_package(OpenGL REQUIRED)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/engine)
