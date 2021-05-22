#include <string>

#include <any_of.hpp>

bool test(const std::string& value)
{
	return srp::any_of(std::string("a")) == value;
}
