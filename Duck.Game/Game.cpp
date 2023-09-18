#include <Engine.h>

using namespace Duck;

#include "Scripts/FlyCamera.h"
#include "Scripts/BoxComponent.h"
//FIX WHEN TWO SAME KEYS ARE DOWN (Reset in poll, check Game.cpp) BETTER MOUSE DELTA INPLEMENTATION
//Add getters and setters for fullscreen, vsync, etc.
//Model should not have pointer to meshes but rather keep meshes in it

//*VERIFY IF TRANSFORM CHILD HAS CORRECT SCALE IN CASE OF PARENT SCALING AND ROTATION
//*FIX AssetsPath string to be independent from system and fix green highlights
//*Fix Null main camera
//*VERIFY MODEL LOADER HIERARCHY
//Remove Graphics Camera dependency from Window (Somehow pass aspect ration as argument)
//Render Layers similar to Unity
//*FIX LOGGER COLOR WHEN RUNNING EXE
//*FIX ALL WARNINGS
//*MAKE SCENE INTO CLASS (CHECK THE TUTORIAL AND REDO IT), ADD SCENES MANAGER, SCENE KEEPS TRACK OF LIGHTS
//Implement lighting, make Light class hold enum type of the light (Similar to Unity)
//Refactor model loading and make sure everything works correctly
//Window - REFACTOR ALL CODE, Clearer code for _lastPosition, _lastWidth, _lastResoultion
//Layered rendering (Weapon always on top of everything)
//Make engine as submodule of the game in github. Move Vendor into Engine and rename Duck.Engine into Duck.
//Events System (Cherno)
//Text Rendering, UI (render always forward) renderer build native C++ with HTML/CSS UI, console
//Particle systems
//Make Scene class and have scene serialization

class Game : App
{
private:
	CameraPerspective camera;
	Scene scene;
	Entity* box = scene.AddEntity();
	BoxComponent* boxComp;

public:
	void Init()
	{
		Window::SetResolution(800, 600);
		Window::SetVSync(true);

		boxComp = box->AddComponent<BoxComponent>();
		box->transform.position = Vector3(0, 0, 5);
		box->transform.scale = Vector3(1.f);
	}

	void Update(float deltaTime)
	{
		scene.Update(deltaTime);
		FlyCamera::Update(deltaTime);

		if (Input::IsKeyPressed(Input::G))
		{
			boxComp->m_Mesh.vertices[0] += Vector3(0, deltaTime, 0);
			boxComp->m_Mesh.UploadData();
		}

		//FIX WHEN TWO SAME KEYS ARE DOWN (Reset in poll)
		if (Input::IsKeyDown(Input::Space))
		{
			float i = Random::Range(1.f, 5.f);
			Logger::Debug("%f", i);
		}

		if (Input::IsKeyDown(Input::Space))
		{
			Lighting::AmbientLight.SetIntensity(Lighting::AmbientLight.GetIntensity() + 0.1f);
		}
	}

	void Draw()
	{
		scene.Draw();
	}

	void Destroy()
	{
		scene.Destroy();
	}
};

int main()
{
	Start<Game>();
	return 0;
}
