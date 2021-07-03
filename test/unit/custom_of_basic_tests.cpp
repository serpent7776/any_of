#include <string>
#include <type_traits>

#include <catch2/catch.hpp>
#include <any_of.hpp>

TEST_CASE("custom any_of with operators == and !=")
{
	auto custom_any_of = srp::make_custom_of<srp::EqOp<srp::logical_or, std::equal_to<void>>, srp::NeqOp<srp::logical_or, std::not_equal_to<void>>>();

	REQUIRE(custom_any_of(1, 2, 3, 4, 5, 6) == 1);
	REQUIRE(not (custom_any_of(1, 2, 3, 4, 5, 6) == 0));

	REQUIRE(custom_any_of(1, 2, 3, 4, 5, 6) != 1);
	REQUIRE(not (custom_any_of(2, 2, 2) != 2));
}

