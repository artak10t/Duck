#pragma once
#include "Entity.h"

namespace Duck
{
	class Scene 
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;

		void removeDestroyedEntites()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity>& mEntity)
				{
					return !mEntity->IsAlive();
				}),
				std::end(entities));
		}

	public:
		void Update(float deltaTime)
		{
			for (int i = 0; i < entities.size(); i++)
				entities[i]->Update(deltaTime);
		}

		void Draw()
		{
			for (int i = 0; i < entities.size(); i++)
				entities[i]->Draw();

			removeDestroyedEntites();
		}

		void Destroy()
		{
			for (int i = 0; i < entities.size(); i++)
				entities[i]->Destroy();

			removeDestroyedEntites();
		}

		Entity* AddEntity()
		{
			Entity* e = new Entity();
			std::unique_ptr<Entity> uPtr{ e };
			entities.emplace_back(std::move(uPtr));
			return e;
		}
	};
}