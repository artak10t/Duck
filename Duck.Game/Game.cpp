#include <Engine.h>
using namespace Duck;

#include "Scripts/FlyCamera.h"
#include "Scripts/BoxComponent.h"
#include "Scripts/Weapon.h"
#include "Scripts/KinematicWeaponAnimation.h"
//*VERIFY IF TRANSFORM CHILD HAS CORRECT SCALE IN CASE OF PARENT SCALING
//*VERIFY MODEL LOADER HIERARCHY
//Redo Assets and Resources system (Follow youtube tutorial), Rename Renderer Polygone
//Remove Graphics Camera dependency from Window (Somehow pass aspect ration as argument)
//Make engine as submodule of the game in github. Move Vendor into Engine and rename Duck.Engine into Duck.
//Compile libraries with engine compilation (No precompiled libraries)
//Precompile shader (Run an executable program for compiling shaders)
//Baked lighting (Run an executable for baking lights)
//Events System (Cherno)
//GLM SIMD Optimization
//Text Rendering, UI (render always forward) renderer, console
//Implement lighting (LATER)
//YAML Entity prefab system (Similar how SS14 does). Resources.Load<Prefab>()
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

		if (Input::KeyDown(Input::Space))
			Lighting::GlobalLight.SetIntensity(Lighting::GlobalLight.GetIntensity() + 0.1f);
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