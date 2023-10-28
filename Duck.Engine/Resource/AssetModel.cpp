#include "AssetModel.h"

#include "../System/Logger.h"

namespace Duck::Resources
{
	static std::unordered_map<const char*, Model*> cache;

	template<>
	Model* Load<Model>(const char* file)
	{
		if (cache.find(file) != cache.end())
			return cache.at(file);

		// Get Path
		std::string path = GetAssetsPath() + file;

		// Cache Model
		Logger::Trace("Model - '%s' loading", file);
		cache.emplace(file, new Model(path.c_str()));

		return cache.at(file);
	}

	template<>
	void Unload<Model>(const char* file)
	{
		if (cache.find(file) == cache.end())
			return;

		delete cache.at(file);
		cache.erase(file);
	}
}