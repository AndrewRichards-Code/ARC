#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace arc
{
	void SaveTextFile(const std::filesystem::path& filepath, const std::string& contents);
	void SaveBinaryFile(const std::filesystem::path& filepath, const std::vector<char>& contents);
}