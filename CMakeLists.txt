cmake_minimum_required(VERSION 3.16)
project(maglass)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

add_executable(main
	"src/main.c"
)

target_link_libraries(main PRIVATE 
	SDL3::SDL3
)
