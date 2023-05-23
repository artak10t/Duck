cmake_minimum_required (VERSION 3.8)

add_executable ($ENV{GAME_NAME} "Game.cpp" "Scripts/FlyCamera.h" "Scripts/BoxComponent.h" "Scripts/KinematicWeaponAnimation.h" "Scripts/Weapon.h")
target_link_libraries($ENV{GAME_NAME} $ENV{ENGINE_NAME})
target_include_directories($ENV{GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/$ENV{ENGINE_NAME}")

#Copy assets into executable folder
add_custom_target(load_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/load_assets.cmake
)
add_dependencies($ENV{GAME_NAME} load_assets)