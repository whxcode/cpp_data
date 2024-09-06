cmake_minimum_required(VERSION 3.10)

# set the project name
project(ProjectName)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# get all .c and .cpp files recursively
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# add the executable with the source files
add_executable(ProjectName ${SOURCES})

