#pragma once

#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
	#ifdef LOJO_STR_UTILS_EXPORTS
		#define LOJO_STR_UTILS_API __declspec(dllexport)
	#else
		#define LOJO_STR_UTILS_API __declspec(dllimport)
	#endif
#else
	#define LOJO_STR_UTILS_API
#endif

/**
  Takes in a format string, parses it, and then
  inserts it into the given char* buffer.

  @param buf The character buffer to insert the final string.
  @param size The buffer's size.
  @param fmt The format string (ex: 'x = %d').
  @param ... The format arguments.
*/
LOJO_STR_UTILS_API void lojo_utils_get_str(char *buf, size_t size, const char *fmt, ...);
