cmake_minimum_required (VERSION 3.8)

add_executable ($ENV{GAME_NAME} "Game.cpp" )

target_link_libraries($ENV{GAME_NAME} $ENV{ENGINE_NAME})
target_include_directories($ENV{GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/$ENV{ENGINE_NAME}")

target_link_libraries($ENV{GAME_NAME} $ENV{COSMO_NAME})
target_include_directories($ENV{GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/$ENV{COSMO_NAME}")

# Copy data into executable folder
file (GLOB_RECURSE ALL_DATA "Data/*.*")
foreach(data ${ALL_DATA})
	get_filename_component(filename ${data} NAME)
	get_filename_component(dir ${data} DIRECTORY)
	get_filename_component(dirname ${dir} NAME)
	
	set (output "")
	
	while(NOT ${dirname} STREQUAL Data)
		get_filename_component(path_component ${dir} NAME)
		set (output "${path_component}/${output}")
		get_filename_component(dir ${dir} DIRECTORY)
		get_filename_component(dirname ${dir} NAME)
	endwhile()

	set(output "${CMAKE_CURRENT_BINARY_DIR}/Data/${output}/${filename}")
 
	add_custom_command(
		COMMENT "Copied Data: '${filename}'"
		OUTPUT ${output}
		DEPENDS $ENV{GAME_NAME} ${data}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${data}
		${output}
	)
	add_custom_target(${filename} ALL DEPENDS ${data} ${output})
endforeach()