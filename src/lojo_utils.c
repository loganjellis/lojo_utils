#include "lojo_str_utils.h"

void lojo_utils_get_str(char *buf, size_t size, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, size, fmt, args);
	va_end(args);
}
