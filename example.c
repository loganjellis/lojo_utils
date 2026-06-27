#include "lojo_str_utils.h"

int main(void)
{
	char buf[48];
	int age = 27;

	lojo_utils_get_str(buf, sizeof buf, "You are %d years old!", age);
	printf("%s\n", buf);

	lojo_utils_get_str(buf, sizeof buf, "You are now %d years old!", age - 10);
	printf("%s\n", buf);

	return 0;
}
