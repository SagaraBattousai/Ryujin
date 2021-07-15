cmake_minimum_required(VERSION 3.16)

project(Ryujin
        VERSION 0.0.1
        DESCRIPTION "Game Not Game Engine"
        LANGUAGES CXX C)

set(CMAKE_C_STANDARD 11)

include(cmake/copy_resources_to_target.cmake)

set(GLAD_HOME "$ENV{GLAD_HOME}" CACHE PATH "Path to GLAD install directory")
set(GLFW_HOME "$ENV{GLFW_HOME}" CACHE PATH "Path to GLFW install directory")

list(APPEND CMAKE_PREFIX_PATH "${GLFW_HOME}" "${GLAD_HOME}")
#set(glfw3_DIR "$ENV{GLFW_HOME}/lib/cmake/")

find_package(glfw3 3.3 REQUIRED) # adds target glfw

find_package(glad 0.1.34 REQUIRED) # adds target glad::glad

set(public_header_root "${CMAKE_SOURCE_DIR}/include" )

add_subdirectory(src/kuraokami)

