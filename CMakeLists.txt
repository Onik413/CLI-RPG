cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(CLI_RPG VERSION 1.0.0 LANGUAGES CXX)

#add_subdirectory(include)
add_subdirectory(app)
#add_subdirectory(src)

add_library(project_options INTERFACE)

target_include_directories(project_options INTERFACE include)
target_compile_features(project_options INTERFACE cxx_std_20)
target_compile_options(project_options INTERFACE -Wall -Wextra -Wpedantic)


