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
					return !mEntity->GetAlive();
				}),
				std::end(entities));
		}

	public:
		static Scene* CurrentScene;
		// On Save (YAML), if current scene name used will overwrite https://github.com/biojppm/rapidyaml
		// Save Renderer Ambient and Directional Lights
		// Iterate over entities and save their transform, // IMPORTANT
		// save their components,  // IMPORTANT
		// and save primitive data from components with [Serialize] field
		static void Save(const char* name);
		// On Load
		// Clean renderer point and spot lights
		// Clean ambient and directional light
		// When loading lightComponent 
		// it automatically will create new light and add to renderer
		// Somehow know component type when load https://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name
		// Take class name using c++ function and in constructor of each component register class. Make sure it is constexpr registery
		static void Load(const char* name);

		Scene(const char* name = "Scene")
		{

		}

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