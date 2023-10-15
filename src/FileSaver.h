#pragma once
#include <string>
#include <vector>


namespace arc
{
	void SaveTextFile(const std::string& filepath, const std::string& contents);
	void SaveBinaryFile(const std::string& filepath, const std::vector<char>& contents);
}