#pragma once

class Weapon : public Component
{
private:
	Model model = Model("C:/Users/Spartak/Desktop/Duck/Duck.Game/Assets/Weapon.glb");
	Shader* shader = Resources::Load<Shader>("Default.shader");
	Texture* texture = Resources::Load<Texture>("Weapon_texture.png", Texture::FilterMode::Point, Texture::WrapMode::Clamp);
public:
	void Init()
	{
		shader->SetInt("texture_0", 0);
	}

	void Draw()
	{
		if (!Camera::GetMain())
			return;

		shader->SetMatrix4("model", entity->transform.LocalToWorld());
		shader->SetVector3("light", Vector3(-15, 15, 15));
		texture->Bind();
		shader->Bind();
		model.Draw();
	}
};