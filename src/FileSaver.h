#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Log.h"

namespace arc
{
	static void SaveTextFile(const std::string& filepath, const std::string& contents)
	{
		std::ofstream stream(filepath, std::fstream::out);
		std::string output;
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not save file %s.", filepath.c_str());
		}
		stream << contents;
		stream.close();
	}
	
	static void SaveBinaryFile(const std::string& filepath, const std::vector<char>& contents)
	{
		std::ofstream stream(filepath, std::fstream::out | std::fstream::binary);
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not save file %s.", filepath.c_str());
		}
		std::streamoff size = static_cast<std::streamoff>(contents.size());
		stream.write(contents.data(), size);
		stream.close();
	}
}