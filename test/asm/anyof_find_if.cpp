#include <string>
#include <vector>
#include <algorithm>

#include <any_of.hpp>

auto test(int a, int b)
{
	const auto vec = std::vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	return std::find(std::begin(vec), std::end(vec), srp::any_of(a, b));
}
