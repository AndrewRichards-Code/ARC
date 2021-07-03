#pragma once

#if defined(_MSC_VER)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#include <Windows.h>

#include <string>

namespace arc
{
	static std::string GetLastErrorToString(DWORD error)
	{
		if (error != 0)
		{
			char* formatedMessage = nullptr;
			DWORD formatedMessageSize = FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, error, 0, (char*)&formatedMessage, 0, nullptr);

			if (formatedMessage != nullptr && formatedMessageSize > 0)
			{
				std::string result(formatedMessage, formatedMessageSize);
				LocalFree(formatedMessage);
				return result;
			}
		}
		return std::string();
	}
}
#endif
