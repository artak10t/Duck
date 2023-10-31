#include <Engine.h>

using namespace Duck;

#include "Script/FlyCamera.h"
#include "Script/BoxComponent.h"
//*VERIFY MODEL LOADER HIERARCHY
//*VERIFY IF TRANSFORM CHILD HAS CORRECT SCALE IN CASE OF PARENT SCALING AND ROTATION
//Remove Graphics Camera dependency from Window (Somehow pass aspect ration as argument)
//Layered rendering (Weapon always on top of everything)
//Text Rendering
//Add glfw icon and executable icon
//Connect scene and lights

class Game : App
{
private:
	CameraPerspective camera;
	Scene scene;
	Entity* box = scene.AddEntity();
	BoxComponent* boxComp;
	
	//Shader* shader = Resources::Load<Shader>("DefaultPBR.glsl");
	//Texture* texture = Resources::Load<Texture>("DamagedHelmet_albedo.jpg");
	//Model* model = Resources::Load<Model>("DamagedHelmet.gltf");
	Transform transform;

public:
	void Init() override
	{
		boxComp = box->AddComponent<BoxComponent>();
		box->transform.position = Vector3(0, 0, 5);
		box->transform.scale = Vector3(1.f);
	}

	void Update(float deltaTime) override
	{
		scene.Update(deltaTime);

		FlyCamera::Update(deltaTime);

		if (Input::GetKey(Input::G))
		{
			boxComp->mesh.vertices[0] += Vector3(0, deltaTime, 0);
			boxComp->mesh.UploadData();
		}

		if (Input::GetKeyDown(Input::Space))
		{
			Renderer::LightAmbient.SetIntensity(Renderer::LightAmbient.GetIntensity() + 0.1f);
		}
	}

	void Draw() override
	{
		scene.Draw();

		//shader->SetMatrix4("model", transform.LocalToWorld());
		//shader->SetMatrix4("mvp", Camera::GetMain()->Projection() * Camera::GetMain()->View() * transform.LocalToWorld());
		//texture->Bind();
		//shader->Bind();
		//model->Draw();
		//shader->Unbind();
		//texture->Unbind();

		//boxComp->Draw();
	}

	void Destroy() override
	{
		scene.Destroy();
	}
};

int main()
{
	Start<Game>();
	return 0;
}
