#include <string>
#include <vector>
#include <algorithm>

auto test(int a, int b)
{
	const auto vec = std::vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	return std::find_if(std::begin(vec), std::end(vec), [a, b](int v)
		{
			return v == a || v == b;
		});
}
