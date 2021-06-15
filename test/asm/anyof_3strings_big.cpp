#include <string>

#include <any_of.hpp>

bool test(const std::string& value)
{
	return value == srp::any_of(
		std::string("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"),
		std::string("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"),
		std::string("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"));
}
