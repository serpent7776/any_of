#include <array>
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

namespace
{
	struct Xor
	{
		int operator()(int a, int b) const
		{
			return a ^ b;
		}
	};

	struct Concat
	{
		template <typename ...Ints>
		std::array<int, sizeof...(Ints)> operator()(Ints... ints) const
		{
			return std::array<int, sizeof...(Ints)> {ints...};
		}
	};

	struct XorOp : srp::Op<Concat, Xor>
	{
		template <typename Pack>
		friend std::array<int, Pack::size> operator^(const Pack& pack, int val)
		{
			return srp::eval<srp::Op<Concat, Xor>>(pack, val);
		}
	};
}

TEST_CASE("custom_of with custom operator ^")
{
	auto xor_of = srp::make_custom_of<XorOp>();

	REQUIRE((xor_of(0, 1, 2, 3) ^ 1) == std::array {1, 0, 3, 2});
	REQUIRE((xor_of(0, 1, 2, 3, 4, 5) ^ 1) == std::array {1, 0, 3, 2, 5, 4});
}
