#include <string>

#include <any_of.hpp>

bool test(const std::string& value)
{
	return srp::any_of(std::string("1"), std::string("2"), std::string("3")) == value;
}
