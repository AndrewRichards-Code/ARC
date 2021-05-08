#pragma once
#include "Log.h"

namespace arc
{
	class DynamicLibrary
	{
	public:
		#if defined(_WIN64)
		typedef HMODULE LibraryHandle;
		#elif defined(__linux__)
		typedef void* LibraryHandle;
		#endif

		typedef void* PFN_LibraryFunction;

		static LibraryHandle Load(const std::string& libraryFilepath)
		{
			LibraryHandle libraryHandle = 0;

			#if defined(_WIN64)
			libraryHandle = LoadLibraryA(libraryFilepath.c_str());
			#elif defined(__linux__)
			libraryHandle = dlopen(libraryFilepath.c_str(), RTLD_NOW | RTLD_NOLOAD);
			#endif
			
			if (!libraryHandle)
			{
				arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, 0, "%s does not exist. Error: %d", libraryFilepath.c_str(), GetLastError());
			}
			return libraryHandle;
		}

		static bool Unload(LibraryHandle& libraryHandle)
		{
			bool success = false;
			#if defined(_WIN64)
			success = FreeLibrary(libraryHandle);
			#elif defined(__linux__)
			success = (dlclose(libraryHandle) == 0);
			#endif

			if (!success)
			{
				arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, 0, "0x%x is not valid. Error: %d", libraryHandle, GetLastError());
			}
			return success;
		}

		static PFN_LibraryFunction LoadFunction(LibraryHandle libraryHandle, const std::string& functionName)
		{
			PFN_LibraryFunction pfn = nullptr;
			#if defined(_WIN64)
			pfn = GetProcAddress(libraryHandle, functionName.c_str());
			#elif defined(__linux__)
			pfn = dlsym(libraryHandle, functionName.c_str());
			#endif

			if (!pfn)
			{
				arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, 0, "Can not load function: %s", functionName.c_str());
			}
			return pfn;
		}
	};
}