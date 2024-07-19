// System
#include "System/Window.h" 
#include "System/Input.h" 
#include "System/Logger.h"
#include "System/Clock.h" 

// Resources
#include "Resource/Resource.h"

// Math
#include "Math/Math.h"
#include "Math/Matrix.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Trigonometry.h"
#include "Math/Vector.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

// Graphics
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Renderer/CameraPerspective.h"
#include "Renderer/CameraOrthographic.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"
#include "Renderer/Light.h"
#include "Renderer/LightDirectional.h"
#include "Renderer/LightPoint.h"
#include "Renderer/LightSpot.h"

// Scene
#include "Scene/Entity.h"
#include "Scene/Component.h"
#include "Scene/Scene.h" 

namespace Duck
{
	class App
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
		virtual void Destroy() = 0;

		template<typename App>
		static void Run()
		{
			// Init App
			Window::Init();
			Input::Init();
			Resources::Init();

			App* app = new App{};
			app->Init();
			Clock updateClock;

			// App Loop
			while (Window::IsOpen())
			{
				// Events
				Input::PollEvents();

				// Logic
				float deltaTime = updateClock.Seconds();
				app->Update(deltaTime);
				updateClock.Restart();

				// Rendering
				Renderer::ClearBuffer();
				Renderer::UpdateCameraUBO();
				Renderer::UpdateLightUBO();
				app->Draw();

				//Scene::Draw();
				Window::SwapBuffers();

				//Events
				Input::ClearEvents();
			}

			// Destroy App
			app->Destroy();
			delete app;
			Window::Destroy();
		}
	};
}