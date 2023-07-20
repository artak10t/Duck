#include "AssetTexture.h"

#include "../System/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace Duck::Resources
{
	static std::unordered_map<const char*, Texture*> m_Cache;

	template<>
	Texture* Load<Texture>(const char* file)
	{
		return Load<Texture>(file, Texture::Filter::Bilinear, Texture::Wrap::Repeat);
	}

	template<>
	Texture* Load<Texture>(const char* file, const Texture::Filter filtering, const Texture::Wrap wrapping)
	{
		if (m_Cache.find(file) != m_Cache.end())
			return m_Cache.at(file);

		// Get Path
		std::string path = GetAssetsPath() + file;

		// Load Texture
		stbi_set_flip_vertically_on_load(true);
		int channels, width, height;
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (stbi_failure_reason())
			DUCK_ASSERT(false, "Texture - %s '%s'", stbi_failure_reason(), file);

		// Cache Texture
		m_Cache.emplace(file, new Texture(textureData, filtering, wrapping, width, height, channels));
		stbi_image_free(textureData);

		Logger::Info("Texture - '%s' Loaded", file);

		return m_Cache.at(file);
	}

	template<>
	void Unload<Texture>(const char* file)
	{
		if (m_Cache.find(file) == m_Cache.end())
			return;

		delete m_Cache.at(file);
		m_Cache.erase(file);
	}
}