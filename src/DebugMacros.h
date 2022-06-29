#pragma once

#include <stdio.h>

//Printf 
#if defined(_DEBUG)
	#if !defined(__ANDROID__)
		#define ARC_PRINTF(fmt, ...) printf_s((fmt), __VA_ARGS__)
	#else
		#define ARC_PRINTF(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "ARC_LOG", fmt, __VA_ARGS__)
	#endif
#else
	#define ARC_PRINTF(fmt, ...)
#endif

//Debugbreak
#if defined(_MSC_VER)
	#define ARC_DEBUG_BREAK __debugbreak()
#else
	#include <signal.h>
	#define ARC_DEBUG_BREAK raise(SIGTRAP)
#endif

//Assert
#if defined(_DEBUG) || defined(ARC_ENABLE_ASSERT)
	#define ARC_ASSERT(x) { if(!(x)) { ARC_DEBUG_BREAK; } }
#else
	#define ARC_ASSERT(x)
#endif