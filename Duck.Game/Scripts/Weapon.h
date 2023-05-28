#pragma once

class Weapon : public Component
{
private:
	Model model = Model("C:/Users/Spartak/Desktop/Duck/Duck.Game/Assets/Weapon.glb");
	Shader* shader = Resources::Load<Shader>("Weapon.shader");
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
		texture->Bind();
		shader->Bind();
		model.Draw();
	}
};