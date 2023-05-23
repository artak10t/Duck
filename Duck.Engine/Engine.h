//Systems
#include "System/Clock.h"
#include "System/Input.h"
#include "System/Logger.h"
#include "System/Resources.h"
#include "System/Window.h"

//Graphics
#include "Graphics/AmbientLight.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraOrthographic.h"
#include "Graphics/CameraPerspective.h"
#include "Graphics/Lighting.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

//Scene
#include "Scene/Component.h"
#include "Scene/Entity.h"
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
	};

	template<typename App>
	void Start()
	{
		Window::Init();
		Input::Init();
		Resources::Init();

		App* app = new App{};
		app->Init();
		Clock updateClock;
		while (Window::IsOpen())
		{
			//Logic
			float deltaTime = updateClock.Seconds();
			Input::PollEvents();
			app->Update(deltaTime);
			Scene::Update(deltaTime);
			updateClock.Restart();

			//Rendering
			Renderer::ClearBuffer();
			Renderer::UpdateGlobalUBO();
			app->Draw();
			Scene::Draw();
			Scene::Refresh();
			Window::SwapBuffers();
		}
		app->Destroy();
		Scene::Destroy();
		delete app;

		Resources::Clear();
		Window::Destroy();
	}
}