#include "Resources.h"
#include "../pch.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <whereami/whereami.h>

#include "Logger.h"

#define ASSETS_FOLDER_NAME "Assets"

//Shader Loading Defaults
#define SHADER_TYPE_TOKEN "#type"
#define SHADER_TYPE_VERTEX "vertex"
#define SHADER_TYPE_FRAGMENT "fragment"

//REFACTOR, POOR IMPLEMENTATION
namespace Duck::Resources
{
	static std::string _assetsPath = "";
	static std::unordered_map<const char*, Texture*> _cachedTextures;
	static std::unordered_map<const char*, Shader*> _cachedShaders;

	static bool _loadShader(const char* path, std::string& vertexData, std::string& fragmentData)
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
				DUCK_ASSERT(type == SHADER_TYPE_VERTEX || type == SHADER_TYPE_FRAGMENT, "Shader - Invalid shader type specification '%s'", path);

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

	void Init()
	{
		//Set assets folder path
		char* path = nullptr;
		int length, dirname_length;

		length = wai_getExecutablePath(NULL, 0, &dirname_length);
		if (length > 0)
		{
			path = (char*)malloc(length + 1);
			wai_getExecutablePath(path, length, &dirname_length);
			path[dirname_length] = '\0';
			_assetsPath = std::string(path) + "/" + ASSETS_FOLDER_NAME + "/";
			free(path);
		}
	}

	void Clear()
	{
		for (std::unordered_map<const char*, Texture*>::iterator itr = _cachedTextures.begin(); itr != _cachedTextures.end(); itr++)
		{
			delete (itr->second);
		}
		_cachedTextures.clear();

		for (std::unordered_map<const char*, Shader*>::iterator itr = _cachedShaders.begin(); itr != _cachedShaders.end(); itr++)
		{
			delete (itr->second);
		}
		_cachedShaders.clear();
	}

	//Texture
	template<>
	Texture* Load<Texture>(const char* file)
	{
		return Load<Texture>(file, Texture::FilterMode::Bilinear, Texture::WrapMode::Repeat);
	}

	template<>
	Texture* Load<Texture>(const char* file, const Texture::FilterMode filtering, const Texture::WrapMode wrapping)
	{
		if (_cachedTextures.find(file) != _cachedTextures.end())
			return _cachedTextures.at(file);

		//Get Path
		std::string path = _assetsPath + file;

		//Load Texture
		stbi_set_flip_vertically_on_load(true);
		int channels, width, height;
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (stbi_failure_reason())
			DUCK_ASSERT(false, "Texture - %s '%s'", stbi_failure_reason(), file);

		//Cache Texture
		_cachedTextures.emplace(file, new Texture(textureData, filtering, wrapping, width, height, channels));
		stbi_image_free(textureData);

		return _cachedTextures.at(file);
	}

	template<>
	void Unload<Texture>(const char* file)
	{
		if (_cachedTextures.find(file) == _cachedTextures.end())
			return;
		
		delete _cachedTextures.at(file);
		_cachedTextures.erase(file);
	}

	//Shader
	template<>
	Shader* Load<Shader>(const char* file)
	{
		if (_cachedShaders.find(file) != _cachedShaders.end())
			return _cachedShaders.at(file);

		//Get Path
		std::string path = _assetsPath + file;

		//Load Shader
		std::string vertexData;
		std::string fragmentData;
		DUCK_ASSERT(_loadShader(path.c_str(), vertexData, fragmentData), "Shader - File doesn't exist '%s'", file);

		//Cache Shader
		_cachedShaders.emplace(file, new Shader(vertexData.c_str(), fragmentData.c_str()));

		return _cachedShaders.at(file);
	}

	template<>
	void Unload<Shader>(const char* file)
	{
		if (_cachedShaders.find(file) == _cachedShaders.end())
			return;

		delete _cachedShaders.at(file);
		_cachedShaders.erase(file);
	}
}