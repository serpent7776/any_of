#include <string>
#include <type_traits>

#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("one_of == returns true if value is unique")
{
	const bool result = srp::one_of(1, 2, 3) == 1;
	REQUIRE(result);
}

TEST_CASE("one_of == returns false if first element duplicates")
{
	const bool result = srp::one_of(3, 2, 3, 4) == 3;
	REQUIRE(not result);
}

TEST_CASE("one_of == returns false if middle element duplicates")
{
	const bool result = srp::one_of(1, 3, 3, 4) == 3;
	REQUIRE(not result);
}

TEST_CASE("one_of == returns false if last element duplicates")
{
	const bool result = srp::one_of(1, 2, 3, 3) == 3;
	REQUIRE(not result);
}

TEST_CASE("one_of == for strings")
{
	const bool result = srp::one_of("foo", "bar", "baz") == "foo";
	REQUIRE(result);
}

TEST_CASE("== one_of returns true if all values equal")
{
	const bool result = 1 == srp::one_of(1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("== one_of returns false if first element not equal")
{
	const bool result = 3 == srp::one_of(3, 2, 3, 4);
	REQUIRE(not result);
}

TEST_CASE("== one_of returns false if middle element not equal")
{
	const bool result = 3 == srp::one_of(1, 3, 3, 4);
	REQUIRE(not result);
}

TEST_CASE("== one_of returns false if last element not equal")
{
	const bool result = 3 == srp::one_of(1, 2, 3, 3);
	REQUIRE(not result);
}

TEST_CASE("== one_of for strings")
{
	const bool result = "foo" == srp::one_of("foo", "bar", "baz");
	REQUIRE(result);
}

