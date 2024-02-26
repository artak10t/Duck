#include "Resource.h"
#include "../pch.h"

#include <whereami/whereami.h>
using whereami_func_t = int (*)(char* out, int capacity, int* dirname_length);

#define DATA_FOLDER_NAME "Data"

namespace Duck::Resources
{
	// Find Cross-Platform Path
	static std::string dataPath = "";

	static std::string whereami_path(whereami_func_t whereami_func) 
	{
		const auto length = whereami_func(nullptr, 0, nullptr);
		if (length == -1)
			return "";

		std::string path(length, '\0');
		whereami_func(&path[0], length, nullptr);
		return path;
	}

	static std::pair<std::string, std::string> whereami_segmented(whereami_func_t whereami_func) 
	{
		const auto length = whereami_func(nullptr, 0, nullptr);
		if (length == -1)
			return { "", "" };

		int path_length;
		std::string buf(length, '\0');
		whereami_func(&buf[0], length, &path_length);
		return { {buf.c_str(), static_cast<std::size_t>(path_length)}, &buf[path_length + 1] };
	}

	void Init()
	{
		dataPath = whereami_segmented(wai_getExecutablePath).first;
		dataPath.append("\\" + std::string(DATA_FOLDER_NAME) + "\\");
	}

	std::string GetDataPath()
	{
		return dataPath;
	}
}