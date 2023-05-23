cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
project("Duck")

SET(ENV{ENGINE_NAME} "Duck.Engine")
SET(ENV{GAME_NAME} "Duck.Game")

add_subdirectory($ENV{ENGINE_NAME})
add_subdirectory($ENV{GAME_NAME})