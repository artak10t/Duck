cmake_minimum_required (VERSION 3.8)

add_library($ENV{ENGINE_NAME} STATIC 
	"Engine.h"

	"Math/Math.h"
	"Math/Matrix.h"
	"Math/Matrix4.h"
	"Math/Quaternion.h"
	"Math/Random.h"
	"Math/Transform.h"
	"Math/Trigonometry.h"
	"Math/Vector.h"
	"Math/Vector2.h"
	"Math/Vector3.h"
	"Math/Vector4.h"

	"Renderer/Renderer.h"
	"Renderer/Renderer.cpp"
	"Renderer/Light.h"
	"Renderer/Light.cpp"
	"Renderer/LightDirectional.h"
	"Renderer/LightDirectional.cpp"
	"Renderer/LightPoint.h"
	"Renderer/LightPoint.cpp"
	"Renderer/LightSpot.h"
	"Renderer/LightSpot.cpp"
	"Renderer/Camera.h"
	"Renderer/Camera.cpp"
	"Renderer/CameraPerspective.h"
	"Renderer/CameraPerspective.cpp"
	"Renderer/CameraOrthographic.h"
	"Renderer/CameraOrthographic.cpp"
	"Renderer/Mesh.h"
	"Renderer/Mesh.cpp"
	"Renderer/Shader.h"
	"Renderer/Shader.cpp"
	"Renderer/Texture.h"
	"Renderer/Texture.cpp"
	"Renderer/Model.h"
	"Renderer/Model.cpp"

	"Resource/Resource.h"
	"Resource/Resource.cpp"
	"Resource/DataTexture.h"
	"Resource/DataTexture.cpp"
	"Resource/DataShader.h"
	"Resource/DataShader.cpp"
	"Resource/DataModel.h"
	"Resource/DataModel.cpp"

	"Scene/Entity.h"
	"Scene/Component.h"
	"Scene/Scene.h" 

	"System/Window.h" 
	"System/Window.cpp" 
	"System/Input.h" 
	"System/Input.cpp"
	"System/Logger.h"
	"System/Clock.h" 
	"System/Clock.cpp"
 )

target_precompile_headers($ENV{ENGINE_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>")
target_include_directories($ENV{ENGINE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Vendor")

# Glad
add_library(glad "../Vendor/glad/glad.h" "../Vendor/glad/glad.c")
target_link_libraries($ENV{ENGINE_NAME} PRIVATE glad)

if(WIN32)
	target_link_libraries($ENV{ENGINE_NAME} PRIVATE debug "${CMAKE_SOURCE_DIR}/Vendor/glfw/win32/glfw3_d.lib" optimized "${CMAKE_SOURCE_DIR}/Vendor/glfw/win32/glfw3.lib")
endif()