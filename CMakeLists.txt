cmake_minimum_required(VERSION 3.15)

project(winant_http LANGUAGES CXX)

# Set C++ settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Get lists of source and header files
file(GLOB_RECURSE ${PROJECT_NAME}_LIST
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE ${PROJECT_NAME}_LIST_H
	"${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.hh"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.hxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.hpp"
)

# Add library
add_library(${PROJECT_NAME} STATIC
	${${PROJECT_NAME}_LIST}
	${${PROJECT_NAME}_LIST_H}
)

# Include necessary directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}"
)

# Include directory
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# Include kbase dir
target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/third_party/KBase/src"
)

# Add necessary defines
target_compile_definitions(${PROJECT_NAME} PRIVATE
	"-DUNICODE -DNOMINMAX"
)

add_subdirectory(third_party/KBase)

target_link_libraries(${PROJECT_NAME} PRIVATE
	kbase
	wininet
)