#include "FileSaver.h"
#include "Log.h"
#include <fstream>

namespace arc
{
	void SaveTextFile(const std::filesystem::path& filepath, const std::string& contents)
	{
		std::ofstream stream(filepath, std::fstream::out);
		std::string output;
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not save file %s.", filepath.generic_string().c_str());
		}
		stream << contents;
		stream.close();
	}
	
	void SaveBinaryFile(const std::filesystem::path& filepath, const std::vector<char>& contents)
	{
		std::ofstream stream(filepath, std::fstream::out | std::fstream::binary);
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not save file %s.", filepath.generic_string().c_str());
		}
		std::streamoff size = static_cast<std::streamoff>(contents.size());
		stream.write(contents.data(), size);
		stream.close();
	}
}