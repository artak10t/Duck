#include "DataShader.h"

#include "../System/Logger.h"

//Shader Loading Defaults
#define SHADER_TYPE_TOKEN "@type"
#define SHADER_TYPE_VERTEX "vertex"
#define SHADER_TYPE_FRAGMENT "fragment"

namespace Duck::Resources
{
	static std::unordered_map<const char*, Shader*> cache;

	static bool ReadShaderFile(const char* path, std::string& vertexData, std::string& fragmentData)
	{
		std::ifstream in(path, std::ios::in, std::ios::binary);
		if (in)
		{
			//Read Shader
			std::string shader;
			in.seekg(0, std::ios::end);
			shader.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&shader[0], shader.size());
			in.close();

			//Split Shader
			size_t typeTokenLength = strlen(SHADER_TYPE_TOKEN);
			size_t pos = shader.find(SHADER_TYPE_TOKEN, 0);
			while (pos != std::string::npos)
			{
				size_t eol = shader.find_first_of("\r\n", pos);
				size_t begin = pos + typeTokenLength + 1;
				std::string type = shader.substr(begin, eol - begin);
				DUCK_ASSERT(type == SHADER_TYPE_VERTEX || type == SHADER_TYPE_FRAGMENT, "Shader - invalid shader type specification '%s'", path);

				size_t nextLinePos = shader.find_first_not_of("\r\n", eol);
				pos = shader.find(SHADER_TYPE_TOKEN, nextLinePos);

				//Save Data
				if (type == SHADER_TYPE_VERTEX)
					vertexData = shader.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shader.size() - 1 : nextLinePos));
				else if (type == SHADER_TYPE_FRAGMENT)
					fragmentData = shader.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shader.size() - 1 : nextLinePos));
			}

			return true;
		}

		return false;
	}

	template<>
	Shader* Load<Shader>(const char* file)
	{
		if (cache.find(file) != cache.end())
			return cache.at(file);

		// Get Path
		std::string path = GetDataPath() + file;

		// Load Shader
		std::string vertexData;
		std::string fragmentData;
		Logger::Trace("Shader - '%s' loading", file);

		DUCK_ASSERT(ReadShaderFile(path.c_str(), vertexData, fragmentData), "Shader - '%s' file not found", file);

		// Cache Shader
		cache.emplace(file, new Shader(vertexData.c_str(), fragmentData.c_str()));

		return cache.at(file);
	}

	template<>
	void Unload<Shader>(const char* file)
	{
		if (cache.find(file) == cache.end())
			return;

		delete cache.at(file);
		cache.erase(file);
	}
}