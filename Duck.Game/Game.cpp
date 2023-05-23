#include <Engine.h>
using namespace Duck;

#include "Scripts/FlyCamera.h"
#include "Scripts/BoxComponent.h"
#include "Scripts/Weapon.h"
#include "Scripts/KinematicWeaponAnimation.h"
//*VERIFY IF TRANSFORM CHILD HAS CORRECT SCALE IN CASE OF PARENT SCALING
//Add Vector Smooth Damp, double check if quaternion slerp and lerp work correct (Compare with glm), 
// double check if Transform constructors work correctly
//Redo Assets and Resources system (Follow youtube tutorial)
//Remove Graphics Camera dependency from Window (Somehow pass aspect ration as argument)
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
		pivot->transform.position = Vector3(.75f, -.75f, 1.5f);
		pivot->transform.scale = Vector3(.25, .25, .5);
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