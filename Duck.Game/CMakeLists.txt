cmake_minimum_required (VERSION 3.8)

add_executable ($ENV{GAME_NAME} "Game.cpp" )

target_link_libraries($ENV{GAME_NAME} $ENV{ENGINE_NAME})
target_include_directories($ENV{GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/$ENV{ENGINE_NAME}")

target_link_libraries($ENV{GAME_NAME} $ENV{COSMO_NAME})
target_include_directories($ENV{GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/$ENV{COSMO_NAME}")

# Copy assets into executable folder
file (GLOB_RECURSE Assets "Asset/*.*")
foreach(asset ${Assets})
	get_filename_component(filename ${asset} NAME)
	get_filename_component(dir ${asset} DIRECTORY)
	get_filename_component(dirname ${dir} NAME)
	
	set (output "")
	
	while(NOT ${dirname} STREQUAL Asset)
		get_filename_component(path_component ${dir} NAME)
		set (output "${path_component}/${output}")
		get_filename_component(dir ${dir} DIRECTORY)
		get_filename_component(dirname ${dir} NAME)
	endwhile()

	set(output "${CMAKE_CURRENT_BINARY_DIR}/Asset/${output}/${filename}")
 
	add_custom_command(
		COMMENT "Updating asset '${filename}'"
		OUTPUT ${output}
		DEPENDS $ENV{GAME_NAME} ${asset}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${asset}
		${output}
	)
	add_custom_target(${filename} ALL DEPENDS ${asset} ${output})
endforeach()