#pragma once
#include "../pch.h"

#include "Component.h"
#include "../Math/Transform.h"

namespace Duck
{
	class Entity
	{
	private:
		static constexpr std::size_t m_MaxComponents = 32;

		using ComponentID = std::size_t;
		using ComponentBitSet = std::bitset<m_MaxComponents>;
		using ComponentArray = std::array<Component*, m_MaxComponents>;

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

		bool m_Alive = true;
		std::vector<std::unique_ptr<Component>> m_Components;
		ComponentArray m_ComponentArray = {};
		ComponentBitSet m_ComponentBitSet;

	public:
		Transform transform;

		bool IsAlive() const { return m_Alive; }
		void Destroy() { m_Alive = false; }

		~Entity()
		{
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->Destroy();
		}

		void Update(float deltaTime)
		{
			for (int i = 0; i < m_Components.size(); i++)
				if (m_Components[i]->enabled)
					m_Components[i]->Update(deltaTime);
		}

		void Draw()
		{
			for (int i = 0; i < m_Components.size(); i++)
				if (m_Components[i]->enabled)
					m_Components[i]->Draw();
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_ComponentBitSet[GetComponentTypeID<T>];
		}

		template<typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));

			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = c;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;

			c->Init();
			return c;
		}

		template<typename T>
		T* GetComponent() const
		{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}
	};
}