#pragma once
#include <Scene/Component.h>
#include <Scene/Entity.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/Camera.h>
#include <Resources/Resources.h>

using namespace Duck;

class Weapon : public Component
{
private:
	Model* m_Model = Resources::Load<Model>("Weapon.glb");
	Shader* m_Shader = Resources::Load<Shader>("Default.shader");
	Texture* m_Texture = Resources::Load<Texture>("Weapon_texture.png", Texture::Filter::Point, Texture::Wrap::Clamp);

public:
	void Init()
	{
		m_Shader->SetInt("texture_0", 0);
	}

	void Draw()
	{
		if (!Camera::GetMain())
			return;

		m_Shader->SetMatrix4("model", entity->transform.LocalToWorld());
		m_Shader->SetVector3("light", Vector3(-15, 15, 15));
		m_Texture->Bind();
		m_Shader->Bind();
		m_Model->Draw();
	}
};