#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Log.h"

namespace arc
{
	std::string ReadTextFile(const std::string& filepath)
	{
		std::ifstream stream(filepath, std::fstream::in);
		std::string output;
		if (!stream.is_open())
		{
			arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, 0, "Could not read file %s. File does not exist.", filepath);
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
	
	std::vector<char> ReadBinaaryFile(const std::string& filepath)
	{
		std::ifstream stream(filepath, std::fstream::in | std::fstream::binary | std::fstream::ate);
		if (!stream.is_open())
		{
			arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, 0, "Could not read file %s. File does not exist.", filepath);
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