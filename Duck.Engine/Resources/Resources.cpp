#include "Resources.h"
#include "../pch.h"

#include <whereami/whereami.h>

#define ASSETS_FOLDER_NAME "Assets"

namespace Duck::Resources
{
	static std::string assetsPath = "";

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
			assetsPath = std::string(path) + "/" + ASSETS_FOLDER_NAME + "/";
			free(path);
		}
	}

	std::string GetAssetsPath()
	{
		return assetsPath;
	}
}