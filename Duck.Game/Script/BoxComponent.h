#pragma once
#include <Scene/Component.h>
#include <Scene/Entity.h>
#include <Renderer/Mesh.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Renderer/Camera.h>
#include <Resource/Resource.h>
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

	Shader* shader = Resources::Load<Shader>("StandardPBR.glsl");
	Texture* box_albedo = Resources::Load<Texture>("BoxAlbedo.png");
	Texture* box_metallic = Resources::Load<Texture>("BoxMetallic.png");

public:
	Mesh mesh = Mesh(vertices, normals, uv, triangles);

	void Init()
	{
		shader->SetInt("albedoMap", 0);
		shader->SetInt("metallicMap", 1);
	}

	void Draw()
	{
		if (!Camera::GetMain())
			return;

		shader->SetMatrix4("model", entity->transform.LocalToWorld());
		shader->SetMatrix4("mvp", Camera::GetMain()->Projection() * Camera::GetMain()->View() * entity->transform.LocalToWorld());
		box_albedo->Bind(0);
		box_metallic->Bind(1);
		shader->Bind();
		mesh.Draw();
		shader->Unbind();
		box_albedo->Unbind();
		box_metallic->Unbind();
	}
};