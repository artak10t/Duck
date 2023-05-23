#pragma once

namespace Duck 
{
	class Entity;

	class Component
	{
	public:
		Entity* entity = nullptr;
		bool enabled = true;

		virtual void Init() {}
		virtual void Update(float deltaTime) {}
		virtual void Draw() {}
		virtual void Destroy() {}
	};
}