#include <algorithm>

#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("any_of with std::find")
{
	const auto vec = std::vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const auto it = std::find(std::begin(vec), std::end(vec), srp::any_of(7, 8));
	REQUIRE(it != std::end(vec));
	REQUIRE((*it == 7 || *it == 8));
}

TEST_CASE("any_of with std::count")
{
	const auto vec = std::vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const auto count = std::count(std::begin(vec), std::end(vec), srp::any_of(7, 8));
	REQUIRE(count == 2);
}

TEST_CASE("any_of with std::remove")
{
	auto vec = std::vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const auto expected = std::vector {1, 2, 3, 4, 5, 6, 9, 10};
	const auto it = std::remove(std::begin(vec), std::end(vec), srp::any_of(7, 8));
	vec.erase(it, std::end(vec));
	REQUIRE(vec == expected);
}

/*
 * // This sadly doesn't work, because 3rd and 4th arguments to std::replace are expected to be of the same type.
 * TEST_CASE("any_of with std::replace")
 * {
 *         auto vec = std::vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 *         const auto expected = std::vector {1, 2, 3, 4, 5, 6, 666, 666, 9, 10};
 *         std::replace(std::begin(vec), std::end(vec), srp::any_of(7, 8), 666);
 *         REQUIRE(vec == expected);
 * }
 */

