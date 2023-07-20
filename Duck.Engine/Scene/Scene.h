#pragma once
#include "Entity.h"

namespace Duck::Scene
{
	std::vector<std::unique_ptr<Entity>> Entities;

	void Refresh()
	{
		Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsAlive();
			}),
			std::end(Entities));
	}

	void Update(float deltaTime)
	{
		for (int i = 0; i < Entities.size(); i++)
			Entities[i]->Update(deltaTime);
	}

	void Draw()
	{
		for (int i = 0; i < Entities.size(); i++)
			Entities[i]->Draw();
	}

	void Destroy()
	{
		for (int i = 0; i < Entities.size(); i++)
			Entities[i]->Destroy();

		Refresh();
	}

	Entity* AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		Entities.emplace_back(std::move(uPtr));
		return e;
	}
}