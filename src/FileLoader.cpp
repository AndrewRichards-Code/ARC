#include "FileLoader.h"
#include "Log.h"
#include <fstream>
#include <filesystem>

namespace arc
{
	std::string ReadTextFile(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath, std::fstream::in);
		std::string output;
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not read file %s. File does not exist.", filepath.generic_string().c_str());
			return "";
		}
		std::string line;
		while (!stream.eof())
		{
			std::getline(stream, line);
			output.append(line + "\n");
		}
		stream.close();
		return output;
	}
	
	std::vector<char> ReadBinaryFile(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath, std::fstream::in | std::fstream::binary | std::fstream::ate);
		if (!stream.is_open())
		{
			ARC_WARN(0, "Could not read file %s. File does not exist.", filepath.generic_string().c_str());
			return {};
		}
		std::streamoff size = stream.tellg();
		std::vector<char> output(static_cast<size_t>(size));
		stream.seekg(0, std::fstream::beg);
		stream.read(output.data(), size);
		stream.close();
		return std::move(output);
	}
}