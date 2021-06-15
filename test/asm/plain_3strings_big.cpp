#include <string>

bool test(const std::string& value)
{
	return value == std::string("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx") ||
		value == std::string("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy") ||
		value == std::string("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
}
