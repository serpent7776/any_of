#include <string>

bool test(const std::string& value)
{
	return value == std::string("1") ||
		value == std::string("2") ||
		value == std::string("3");
}
