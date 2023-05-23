#pragma once

class BoxComponent : public Component
{
private:
	std::vector<Vertex> vertices =
	{
		{Vector3(1, 1, -1), Vector3(1, 0, 1), Vector3(1), Vector2(1, 1)},
		{Vector3(1, -1, -1), Vector3(0, 1, 1), Vector3(1), Vector2(1, 0)},
		{Vector3(-1, -1, -1), Vector3(1, 1, 0), Vector3(1), Vector2(0, 0)},
		{Vector3(-1, 1, -1), Vector3(0, 1, 1), Vector3(1), Vector2(0, 1)},
		{Vector3(1, 1, 1), Vector3(1, 0, 1), Vector3(1), Vector2(0, 1)},
		{Vector3(1, -1, 1), Vector3(1, 1, 0), Vector3(1), Vector2(0, 0)},
		{Vector3(-1, -1, 1), Vector3(0, 1, 1), Vector3(1), Vector2(1, 0)},
		{Vector3(-1, 1, 1), Vector3(1, 0, 0), Vector3(1), Vector2(1, 1)},
		{Vector3(-1, 1, 1), Vector3(0, 1, 1), Vector3(1), Vector2(0, 0)},
		{Vector3(1, -1, 1), Vector3(1, 0, 1), Vector3(1), Vector2(1, 1)},
		{Vector3(1, 1, 1), Vector3(1, 1, 0), Vector3(1), Vector2(1, 0)},
		{Vector3(-1, -1, 1), Vector3(0, 1, 1), Vector3(1), Vector2(0, 1)},
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 3, 1, 2, 3,
		0, 4, 1, 1, 4, 5,
		2, 7, 3, 2, 6, 7,
		4, 7, 5, 5, 7, 6,
		0, 3, 10, 3, 8, 10,
		1, 9, 2, 2, 9, 11
	};

	Mesh mesh = Mesh(vertices, indices);
	Shader* shader = Resources::Load<Shader>("Default.shader");
	Texture* texture = Resources::Load<Texture>("used-stainless-steel2_albedo.png");
public:
	void Init()
	{
		shader->SetInt("texture_0", 0);
	}

	void Draw()
	{
		if (!Camera::GetMain())
			return;

		shader->SetMatrix4("position", entity->transform.LocalToWorld());
		texture->Bind();
		shader->Bind();
		mesh.Draw();
	}
};