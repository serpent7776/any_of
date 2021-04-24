#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("equals_to_any_of finds first value")
{
	const bool result = equals_to_any_of(1, 1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("equals_to_any_of finds last value")
{
	const bool result = equals_to_any_of(3, 1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("equals_to_any_of returns false if value not found")
{
	const bool result = equals_to_any_of(9, 1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("equals_to_any_of for strings")
{
	const bool result = equals_to_any_of("foo", "baz", "bar", "foo");
	REQUIRE(result);
}
