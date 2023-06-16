#include "AssetTexture.h"

#include "../System/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace Duck::Resources
{
	static std::unordered_map<const char*, Texture*> cachedTextures;

	template<>
	Texture* Load<Texture>(const char* file)
	{
		return Load<Texture>(file, Texture::Filter::Bilinear, Texture::Wrap::Repeat);
	}

	template<>
	Texture* Load<Texture>(const char* file, const Texture::Filter filtering, const Texture::Wrap wrapping)
	{
		if (cachedTextures.find(file) != cachedTextures.end())
			return cachedTextures.at(file);

		// Get Path
		std::string path = AssetsPath + file;

		// Load Texture
		stbi_set_flip_vertically_on_load(true);
		int channels, width, height;
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (stbi_failure_reason())
			DUCK_ASSERT(false, "Texture - %s '%s'", stbi_failure_reason(), file);

		// Cache Texture
		cachedTextures.emplace(file, new Texture(textureData, filtering, wrapping, width, height, channels));
		stbi_image_free(textureData);

		Logger::Info("Texture - '%s' Loaded", file);

		return cachedTextures.at(file);
	}

	template<>
	void Unload<Texture>(const char* file)
	{
		if (cachedTextures.find(file) == cachedTextures.end())
			return;

		delete cachedTextures.at(file);
		cachedTextures.erase(file);
	}
}