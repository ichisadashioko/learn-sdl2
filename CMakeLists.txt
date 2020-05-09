cmake_minimum_required(VERSION 3.10)

# set the project name
project(sdlapp)

# add the executable
add_executable(${PROJECT_NAME} src/main.cc)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})