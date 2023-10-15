#include "DynamicLibrary.h"
#include "Log.h"
#include "WindowsErrorHandling.h"
#include "StringConversion.h"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#endif

using namespace arc;

DynamicLibrary::LibraryHandle DynamicLibrary::Load(const std::string& libraryFilepath)
{
	LibraryHandle libraryHandle = 0;

#if defined(_WIN64)
	#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP)
		std::wstring libraryName = ToWString(libraryFilepath.substr(libraryFilepath.find_last_of('/') + 1));
		libraryHandle = LoadPackagedLibrary(libraryName.c_str(), 0);
	#elif !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
		libraryHandle = LoadLibraryA(libraryFilepath.c_str());
	#endif
	if (!libraryHandle)
	{
		DWORD errorCode = GetLastError();
		ARC_WARN(errorCode, "%s does not exist. GetLastError: %s", libraryFilepath.c_str(), GetLastErrorToString(errorCode).c_str());
	}
#elif defined(__linux__)
	libraryHandle = dlopen(libraryFilepath.c_str(), RTLD_NOW | RTLD_NOLOAD);
	if (!libraryHandle)
	{
		ARC_WARN(0, "%s does not exist. dlerror: %s", libraryFilepath.c_str(), dlerror());
	}
#endif

	return libraryHandle;
}

bool DynamicLibrary::Unload(LibraryHandle& libraryHandle)
{
	bool success = false;

#if defined(_WIN64)
	success = FreeLibrary((HMODULE)libraryHandle);
	if (!success)
	{
		DWORD errorCode = GetLastError();
		ARC_WARN(errorCode, "0x%x is not valid. GetLastError: %s", libraryHandle, GetLastErrorToString(errorCode).c_str());
	}
#elif defined(__linux__)
	success = (dlclose(libraryHandle) == 0);
	if (!success)
	{
		ARC_WARN(0, "0x%x is not valid. dlerror: %s", libraryHandle, dlerror());
	}
#endif

	return success;
}

DynamicLibrary::PFN_LibraryFunction DynamicLibrary::LoadFunction(LibraryHandle libraryHandle, const std::string& functionName)
{
	PFN_LibraryFunction pfn = nullptr;

#if defined(_WIN64)
	pfn = GetProcAddress((HMODULE)libraryHandle, functionName.c_str());
	if (!pfn)
	{
		DWORD errorCode = GetLastError();
		ARC_WARN(errorCode, "Can not load function: %s. GetLastError: %s", functionName.c_str(), GetLastErrorToString(errorCode).c_str());
	}
#elif defined(__linux__)
	pfn = dlsym(libraryHandle, functionName.c_str());
	if (!pfn)
	{
		ARC_WARN(0, "Can not load function: %s. dlerror: %s", functionName.c_str(), dlerror());
	}
#endif

	return pfn;
}
