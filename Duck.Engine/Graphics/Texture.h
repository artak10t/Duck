#pragma once

namespace Duck
{
	class Texture final
	{
	public:
		enum class Wrap
		{
			Repeat,
			Clamp,
			Mirror
		};

		enum class Filter
		{
			Point,
			Bilinear,
			Trilinear
		};

		Texture(unsigned char* textureData, const Filter& filtering = Filter::Bilinear, const Wrap& wrapping = Wrap::Repeat, int width = 64, int height = 64, int channels = 4);
		void Bind(const unsigned int& slot = 0);

	private:
		unsigned int texture = 0;
	};
}