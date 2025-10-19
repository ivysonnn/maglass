cmake_minimum_required(VERSION 3.16)
project(maglass)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")

find_package(raylib REQUIRED)

add_library(mag INTERFACE)
target_include_directories(mag INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.c
	src/handle_input.c
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
	raylib
	m
	X11
	mag
)
