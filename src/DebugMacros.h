#pragma once

#include <stdio.h>

//Debugbreak
#if defined(_MSC_VER)
	#define ARC_DEBUG_BREAK __debugbreak()
#else
	#include <signal.h>
	#define ARC_DEBUG_BREAK raise(SIGTRAP)
#endif

//Asset
#if defined(_DEBUG) || defined(ARC_ENABLE_ASSERT)
	#define ARC_ASSERT(x) { if(!(x)) { ARC_DEBUG_BREAK; } }
#else
	#define ARC_ASSERT(x)
#endif

//Function signature
#if defined(_WIN64)
	#define ARC_FUNCSIG __FUNCSIG__
#elif(__linux__)
	#define ARC_FUNCSIG __PRETTY_FUNCTION__
#endif