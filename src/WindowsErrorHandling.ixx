module;
#include "WindowsInclude.h"

export module ARC:WindowsErrorHandling;
import std.core;

export namespace arc
{
	const std::string GetLastErrorToString(DWORD error)
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
