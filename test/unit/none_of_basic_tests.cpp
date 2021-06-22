#include <string>
#include <type_traits>

#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("none_of == returns true is value not found")
{
	const bool result = srp::none_of(1, 2, 3) == 7;
	REQUIRE(result);
}

TEST_CASE("none_of == returns false is value matches first element")
{
	const bool result = srp::none_of(1, 2, 3) == 1;
	REQUIRE(not result);
}

TEST_CASE("none_of == returns false is value matches middle element")
{
	const bool result = srp::none_of(1, 2, 3) == 2;
	REQUIRE(not result);
}

TEST_CASE("none_of == returns false is value matches last element")
{
	const bool result = srp::none_of(1, 2, 3) == 3;
	REQUIRE(not result);
}

TEST_CASE("none_of == for strings")
{
	const bool result = srp::none_of("foo", "bar", "baz") == "bla";
	REQUIRE(result);
}

TEST_CASE("== none_of returns true is value not found")
{
	const bool result = 7 == srp::none_of(1, 2, 3);
	REQUIRE(result);
}

TEST_CASE("== none_of returns false is value matches first element")
{
	const bool result = 1 == srp::none_of(1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("== none_of returns false is value matches middle element")
{
	const bool result = 2 == srp::none_of(1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("== none_of returns false is value matches last element")
{
	const bool result = 3 == srp::none_of(1, 2, 3);
	REQUIRE(not result);
}

TEST_CASE("== none_of for strings")
{
	const bool result = "bla" == srp::none_of("foo", "bar", "baz");
	REQUIRE(result);
}

