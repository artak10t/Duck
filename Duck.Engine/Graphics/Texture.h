#pragma once

namespace Duck
{
	class Texture final
	{
	public:
		enum class WrapMode
		{
			Repeat,
			Clamp,
			Mirror
		};

		enum class FilterMode
		{
			Point,
			Bilinear,
			Trilinear
		};

		Texture(unsigned char* textureData, const FilterMode& filtering = FilterMode::Bilinear, const WrapMode& wrapping = WrapMode::Repeat, int width = 64, int height = 64, int channels = 4);
		void Bind(const unsigned int& slot = 0);

	private:
		unsigned int _textures = 0;
	};
}