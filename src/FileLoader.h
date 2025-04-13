#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace arc
{
	std::string ReadTextFile(const std::filesystem::path& filepath);
	std::vector<char> ReadBinaryFile(const std::filesystem::path& filepath);
}