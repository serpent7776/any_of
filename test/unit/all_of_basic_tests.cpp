#include <string>
#include <type_traits>

#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("all_of == returns true is all values equal")
{
	const bool result = srp::all_of(1, 1, 1) == 1;
	REQUIRE(result);
}

TEST_CASE("all_of == returns false if first element not equal")
{
	const bool result = srp::all_of(0, 2, 2) == 2;
	REQUIRE(not result);
}

TEST_CASE("all_of == returns false if middle element not equal")
{
	const bool result = srp::all_of(2, 0, 2) == 2;
	REQUIRE(not result);
}

TEST_CASE("all_of == returns false if last element not equal")
{
	const bool result = srp::all_of(2, 2, 0) == 3;
	REQUIRE(not result);
}

TEST_CASE("all_of == for strings")
{
	const bool result = srp::all_of("foo", "foo", "foo") == "foo";
	REQUIRE(result);
}

TEST_CASE("== all_of returns true is all values equal")
{
	const bool result = 1 == srp::all_of(1, 1, 1);
	REQUIRE(result);
}

TEST_CASE("== all_of returns false if first element not equal")
{
	const bool result = 2 == srp::all_of(0, 2, 2);
	REQUIRE(not result);
}

TEST_CASE("== all_of returns false if middle element not equal")
{
	const bool result = 2 == srp::all_of(2, 0, 2);
	REQUIRE(not result);
}

TEST_CASE("== all_of returns false if last element not equal")
{
	const bool result = 2 == srp::all_of(2, 2, 0);
	REQUIRE(not result);
}

TEST_CASE("== all_of for strings")
{
	const bool result = "foo" == srp::all_of("foo", "foo", "foo");
	REQUIRE(result);
}

