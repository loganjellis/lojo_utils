#pragma once

#ifdef _WIN32
	#ifdef LOJO_UTILS_EXPORTS
		#define LOJO_UTILS_API __declspec(dllexport)
	#else
		#define LOJO_UTILS_API __declspec(dllimport)
	#endif
#else
	#define LOJO_UTILS_API
#endif
