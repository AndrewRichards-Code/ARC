#pragma once

#include <string>
#include <vector>

namespace arc
{
	std::string ReadTextFile(const std::string& filepath);
	std::vector<char> ReadBinaryFile(const std::string& filepath);
}