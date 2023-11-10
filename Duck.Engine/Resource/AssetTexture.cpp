#include "AssetTexture.h"

#include "../System/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Duck::Resources
{
	static std::unordered_map<const char*, Texture*> cache;

	template<>
	Texture* Load<Texture>(const char* file)
	{
		return Load<Texture>(file, Texture::Filter::Bilinear, Texture::Wrap::Repeat);
	}

	template<>
	Texture* Load<Texture>(const char* file, const Texture::Filter filtering, const Texture::Wrap wrapping)
	{
		if (cache.find(file) != cache.end())
			return cache.at(file);

		// Get Path
		std::string path = GetAssetsPath() + file;

		// Load Texture
		stbi_set_flip_vertically_on_load(true);
		int channels, width, height;
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (textureData == nullptr && stbi_failure_reason())
			DUCK_ASSERT(false, "Texture - %s '%s'", stbi_failure_reason(), file);

		// Cache Texture
		Logger::Trace("Texture - '%s' loading", file);

		cache.emplace(file, new Texture(textureData, filtering, wrapping, width, height, channels));
		stbi_image_free(textureData);

		return cache.at(file);
	}

	template<>
	void Unload<Texture>(const char* file)
	{
		if (cache.find(file) == cache.end())
			return;

		delete cache.at(file);
		cache.erase(file);
	}
}