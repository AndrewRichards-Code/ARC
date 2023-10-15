#pragma once

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
#elif defined(__linux__)
	#define ARC_FUNCSIG __PRETTY_FUNCTION__
#endif

//C++ Versions
#if defined(_WIN64)
	#define ARC_CXX20 _HAS_CXX20
	#define ARC_CXX17 _HAS_CXX17
#elif defined(__linux__)
	#define ARC_CXX20 (__cplusplus == 202002L)
	#define ARC_CXX17 (__cplusplus == 201703L)
#endif