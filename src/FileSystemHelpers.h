#pragma once
#include<string>
#include<filesystem>

namespace arc
{
	bool FileExist(const std::string& filepath)
	{
		return std::filesystem::exists(std::filesystem::path(filepath));
	}
	std::filesystem::file_time_type FileLastWriteRime(const std::string& filepath)
	{
		if (FileExist(filepath))
			return std::filesystem::last_write_time(std::filesystem::path(filepath));
		else
			return std::filesystem::file_time_type();
	}
}