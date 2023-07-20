#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	struct GlobalLight
	{
	private:
		Vector3 m_Light = Vector3(1.f);
		Vector3 m_Color = Vector3(1.f);
		float m_Intensity = .5f;

	public:
		GlobalLight()
		{
			m_Light = m_Color * m_Intensity;
		}

		inline const Vector3& GetColor()
		{
			return m_Color;
		}

		inline const float GetIntensity()
		{
			return m_Intensity;
		}

		inline void SetColor(const Vector3& color)
		{
			this->m_Color = color;
			m_Light = color * m_Intensity;
		}

		inline void SetIntensity(const float& intensity)
		{
			this->m_Intensity = intensity;
			m_Light = m_Color * intensity;
		}

		inline const Vector3& GetLight()
		{
			return m_Light;
		}
	};
}