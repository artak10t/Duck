#pragma once
#include <Scene/Component.h>
#include <Scene/Entity.h>
#include <Graphics/Mesh.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/Camera.h>
#include <Resources/Resources.h>
#include <System/Logger.h>

using namespace Duck;

class BoxComponent : public Component
{
private:
	std::vector<Vector3> vertices =
	{	
		Vector3(1, 1, -1), Vector3(1, -1, -1),
		Vector3(-1, -1, -1), Vector3(-1, 1, -1),
		Vector3(1, 1, 1), Vector3(1, -1, 1),
		Vector3(-1, -1, 1), Vector3(-1, 1, 1),
		Vector3(-1, 1, 1), Vector3(1, -1, 1),
		Vector3(1, 1, 1), Vector3(-1, -1, 1)
	};

	std::vector<Vector3> normals =
	{
		Vector3(1, 1, -1), Vector3(1, -1, -1),
		Vector3(-1, -1, -1), Vector3(-1, 1, -1),
		Vector3(1, 1, 1), Vector3(1, -1, 1),
		Vector3(-1, -1, 1), Vector3(-1, 1, 1),
		Vector3(-1, 1, 1), Vector3(1, -1, 1),
		Vector3(1, 1, 1), Vector3(-1, -1, 1)
	};

	std::vector<Vector2> uv =
	{
		Vector2(1, 1), Vector2(1, 0),
		Vector2(0, 0), Vector2(0, 1),
		Vector2(0, 1), Vector2(0, 0),
		Vector2(1, 0), Vector2(1, 1),
		Vector2(0, 0), Vector2(1, 1),
		Vector2(1, 0), Vector2(0, 1)
	};

	std::vector<unsigned int> triangles =
	{
		0, 1, 3, 1, 2, 3,
		0, 4, 1, 1, 4, 5,
		2, 7, 3, 2, 6, 7,
		4, 7, 5, 5, 7, 6,
		0, 3, 10, 3, 8, 10,
		1, 9, 2, 2, 9, 11
	};

	Shader* shader = Resources::Load<Shader>("Default.shader");
	Texture* texture = Resources::Load<Texture>("metalbox_diffuse.png");

public:
	Mesh mesh = Mesh(vertices, normals, uv, triangles);

	void Init()
	{
		Logger::Debug("Init");
		shader->SetInt("texture_0", 0);
	}

	void Draw()
	{
		if (!Camera::GetMain())
			return;

		shader->SetMatrix4("model", entity->transform.LocalToWorld());
		shader->SetMatrix4("mvp", Camera::GetMain()->Projection() * Camera::GetMain()->View() * entity->transform.LocalToWorld());
		texture->Bind();
		shader->Bind();
		mesh.Draw();
	}
};