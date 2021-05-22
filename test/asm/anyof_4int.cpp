#include <any_of.hpp>

bool test(int value)
{
	return value == srp::any_of(10, 11, 12, 13);
}
