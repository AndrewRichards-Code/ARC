#pragma once

#if defined(_MSC_VER)
//  Microsoft 
	#define ARC_EXPORT __declspec(dllexport)
	#define ARC_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
	#define ARC_EXPORT __attribute__((visibility("default")))
	#define ARC_IMPORT
#else
//  do nothing and hope for the best?
	#define ARC_EXPORT
	#define ARC_IMPORT
	#pragma warning Unknown dynamic link import/export semantics.
#endif