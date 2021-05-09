#pragma once
#include<string>
#include<filesystem>

namespace arc
{
	static bool FileExist(const std::string& filepath)
	{
		return std::filesystem::exists(std::filesystem::path(filepath));
	}
	static std::filesystem::file_time_type FileLastWriteTime(const std::string& filepath)
	{
		if (FileExist(filepath))
			return std::filesystem::last_write_time(std::filesystem::path(filepath));
		else
			return std::filesystem::file_time_type();
	}
}