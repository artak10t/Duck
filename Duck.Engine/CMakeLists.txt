cmake_minimum_required (VERSION 3.8)

add_library($ENV{ENGINE_NAME} STATIC 
	"Engine.h"
	"System/Window.h" 
	"System/Window.cpp" 
	"System/Input.h" 
	"System/Input.cpp"
	"System/Logger.h"
	"System/Clock.h" 
	"System/Clock.cpp"
	"System/Resources.h"
	"System/Resources.cpp"
	"Graphics/Renderer.h"
	"Graphics/Renderer.cpp"
	"Graphics/Lighting.h"
	"Graphics/Lighting.cpp"
	"Graphics/AmbientLight.h"
	"Graphics/Camera.h"
	"Graphics/Camera.cpp"
	"Graphics/CameraPerspective.h"
	"Graphics/CameraPerspective.cpp"
	"Graphics/CameraOrthographic.h"
	"Graphics/CameraOrthographic.cpp"
	"Graphics/Mesh.h"
	"Graphics/Mesh.cpp"
	"Graphics/Shader.h"
	"Graphics/Shader.cpp"
	"Graphics/Texture.h"
	"Graphics/Texture.cpp"
	"Scene/Entity.h"
	"Scene/Component.h"
	"Scene/Scene.h" 
)

target_precompile_headers($ENV{ENGINE_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>")
target_include_directories($ENV{ENGINE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Vendor")

#OpenGL Loader
add_library(glad "../Vendor/glad/glad.h" "../Vendor/glad/glad.c")
target_link_libraries($ENV{ENGINE_NAME} PRIVATE glad)

if(WIN32)
	target_link_libraries($ENV{ENGINE_NAME} PRIVATE debug "${CMAKE_SOURCE_DIR}/Vendor/glfw/win32/glfw3_d.lib" optimized "${CMAKE_SOURCE_DIR}/Vendor/glfw/win32/glfw3.lib")
endif()