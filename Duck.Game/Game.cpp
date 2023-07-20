#include <Engine.h>

using namespace Duck;

#include "Scripts/FlyCamera.h"
#include "Scripts/BoxComponent.h"
#include "Scripts/Weapon.h"
#include "Scripts/KinematicWeaponAnimation.h"
//*VERIFY IF TRANSFORM CHILD HAS CORRECT SCALE IN CASE OF PARENT SCALING AND ROTATION
//*FIX AssetsPath string to be independent from system and fix green highlights
//*Fix Null main camera
//*VERIFY MODEL LOADER HIERARCHY
//*FIX WHEN TWO SAME KEYS ARE DOWN (Reset in poll, check Game.cpp) BETTER MOUSE DELTA INPLEMENTATION
//*FIX LOGGER COLOR WHEN RUNNING EXE
//*FIX ALL WARNINGS
//*MAKE SCENE INTO CLASS (CHECK THE TUTORIAL AND REDO IT), ADD SCENES MANAGER, SCENE KEEPS TRACK OF LIGHTS
//Implement lighting, make Light class hold enum type of the light (Similar to Unity)
//Refactor model loading and make sure everything works correctly
//Window - REFACTOR ALL CODE, Clearer code for _lastPosition, _lastWidth, _lastResoultion
//Layered rendering (Weapon always on top of everything)
//Remove Graphics Camera dependency from Window (Somehow pass aspect ration as argument)
//Make engine as submodule of the game in github. Move Vendor into Engine and rename Duck.Engine into Duck.
//Events System (Cherno)
//Precompile shader (Run an executable program for compiling shaders)
//Text Rendering, UI (render always forward) renderer build native C++ with HTML/CSS UI, console
//Particle systems
//LUA SCRIPTING
//YAML Entity prefab system (Similar how SS14 does). Resources.Load<Prefab>()
//Make Scene class and have scene serialization
//Scriptable Object DataAsset equivalent (Maybe use YAML for data)

class Game : App
{
private:
	CameraPerspective camera;
	Entity* weapon = Scene::AddEntity();
	Entity* pivot = Scene::AddEntity();
	Entity* box2 = Scene::AddEntity();

public:
	void Init()
	{
		Window::SetResolution(800, 600);

		pivot->transform.parent = &camera.transform;
		pivot->transform.position = Vector3(.25f, -.4f, .3f);
		weapon->transform.parent = &pivot->transform;
		weapon->AddComponent<Weapon>();
		weapon->AddComponent<KinematicWeaponAnimation>();

		box2->AddComponent<BoxComponent>();
		box2->transform.position = Vector3(0, 0, 5);
		box2->transform.scale = Vector3(1.f);
	}

	void Update(float deltaTime)
	{
		FlyCamera::Update(deltaTime);

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

	}

	void Destroy()
	{

	}
};

int main()
{
	Start<Game>();
	return 0;
}