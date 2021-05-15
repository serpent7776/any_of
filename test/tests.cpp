#include <string>

#include <catch2/catch.hpp>
#include <any_of.hpp>

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

TEST_CASE("any_of as lvalue")
{
	const auto value = std::string("foo");
	const auto values = srp::any_of(std::string("foo"), std::string("bar"), std::string("baz"));
	REQUIRE(values == value);
	REQUIRE(value == values);
}
