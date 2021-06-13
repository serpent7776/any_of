#include <string>
#include <algorithm>
#include <type_traits>

#include <catch2/catch.hpp>
#include <any_of.hpp>

static_assert(std::is_aggregate_v<decltype(srp::any_of(12))>);
static_assert(std::is_aggregate_v<srp::Value<0, int>>);

TEST_CASE("equals_to_any_of finds first value")
{
	const bool result = srp::equals_to_any_of(1, 1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("equals_to_any_of finds last value")
{
	const bool result = srp::equals_to_any_of(3, 1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("equals_to_any_of returns false if value not found")
{
	const bool result = srp::equals_to_any_of(9, 1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("equals_to_any_of for strings")
{
	const bool result = srp::equals_to_any_of("foo", "baz", "bar", "foo");
	REQUIRE(result);
}

TEST_CASE("any_of == finds first value")
{
	const bool result = srp::any_of(1, 2, 3) == 1;
	REQUIRE(result);
}

TEST_CASE("any_of == finds last value")
{
	const bool result = srp::any_of(1, 2, 3) == 3;
	REQUIRE(result);
}

TEST_CASE("any_of == returns false if value not found")
{
	const bool result = srp::any_of(1, 2, 3) == 9;
	REQUIRE(not result);
}

TEST_CASE("any_of == for strings")
{
	const bool result = srp::any_of("foo", "bar", "baz") == "foo";
	REQUIRE(result);
}

TEST_CASE("== any_of finds first value")
{
	const bool result = 1 == srp::any_of(1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("== any_of finds last value")
{
	const bool result = 3 == srp::any_of(1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("== any_of returns false if value not found")
{
	const bool result = 9 == srp::any_of(1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("== any_of for strings")
{
	const bool result = "foo" == srp::any_of("foo", "bar", "baz");
	REQUIRE(result);
}

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

/*
 * // This doesn't work either, because std::equal_range uses std::less, which also forces its lhs and rhs to be of the same type.
 * TEST_CASE("any_of with std::equal_range")
 * {
 *         const auto vec = std::vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 *         const auto [f, l] = std::equal_range(std::begin(vec), std::end(vec), srp::any_of(7, 8));
 *         REQUIRE(*f == 7);
 *         REQUIRE(*l == 8);
 * }
 */

