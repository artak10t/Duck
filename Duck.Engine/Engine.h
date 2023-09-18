// System
#include "System/Window.h" 
#include "System/Input.h" 
#include "System/Logger.h"
#include "System/Clock.h" 

// Resources
#include "Resources/Resources.h"

// Math
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
#include "Graphics/Renderer.h"
#include "Graphics/Lighting.h"
#include "Graphics/GlobalLight.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraPerspective.h"
#include "Graphics/CameraOrthographic.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Model.h"

// Scene
#include "Scene/Entity.h"
#include "Scene/Component.h"
#include "Scene/Scene.h" 

namespace Duck
{
	// Pure virtual class App
	class App
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
		virtual void Destroy() = 0;
	};

	template<typename App>
	void Start()
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

			// Logic Frame
			float deltaTime = updateClock.Seconds();
			app->Update(deltaTime);
			//Scene::Update(deltaTime);
			updateClock.Restart();

			// Rendering
			Renderer::ClearBuffer();
			Renderer::UpdateGlobalUBO();
			app->Draw();
			//Scene::Draw();
			Window::SwapBuffers();

			//Events
			Input::CleanEvents();
		}

		// Destroy App
		app->Destroy();
		//Scene::Destroy();
		delete app;

		Window::Destroy();
	}
}