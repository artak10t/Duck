#pragma once
#include "../pch.h"

#include "Component.h"
#include "../Math/Transform.h"

namespace Duck
{
	class Entity
	{
	private:
		static constexpr std::size_t maxComponents = 32;

		using ComponentID = std::size_t;
		using ComponentBitSet = std::bitset<maxComponents>;
		using ComponentArray = std::array<Component*, maxComponents>;

		static inline ComponentID GetComponentTypeID()
		{
			static ComponentID lastID = 0;
			return lastID++;
		}

		template<typename T>
		static inline ComponentID GetComponentTypeID() noexcept
		{
			static ComponentID typeID = GetComponentTypeID();
			return typeID;
		}

		bool isAlive = true;
		std::vector<std::unique_ptr<Component>> components;
		ComponentArray componentArray = {};
		ComponentBitSet componentBitSet;

	public:
		const char* name = "Entity";
		Transform transform;

		bool GetAlive() const { return isAlive; }
		void Destroy() { isAlive = false; }

		~Entity()
		{
			for (int i = 0; i < components.size(); i++)
				components[i]->Destroy();
		}

		void Update(float deltaTime)
		{
			for (int i = 0; i < components.size(); i++)
				if (components[i]->enabled)
					components[i]->Update(deltaTime);
		}

		void Draw()
		{
			for (int i = 0; i < components.size(); i++)
				if (components[i]->enabled)
					components[i]->Draw();
		}

		template<typename T>
		bool HasComponent() const
		{
			return componentBitSet[GetComponentTypeID<T>];
		}

		template<typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));

			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));

			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;

			c->Init();
			return c;
		}

		template<typename T>
		T* GetComponent() const
		{
			auto ptr(componentArray[GetComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}
	};
}