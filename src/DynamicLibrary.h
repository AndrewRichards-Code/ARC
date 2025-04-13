#pragma once
#include <filesystem>
#include <string>

namespace arc
{
	class DynamicLibrary
	{
	public:
		typedef void* LibraryHandle;
		typedef void* PFN_LibraryFunction;

		static LibraryHandle Load(const std::filesystem::path& libraryFilepath);
		static bool Unload(LibraryHandle& libraryHandle);

		static PFN_LibraryFunction LoadFunction(LibraryHandle libraryHandle, const std::string& functionName);
	};
}