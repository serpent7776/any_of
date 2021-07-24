#include <array>
#include <functional>
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
	struct Concat
	{
		template <typename ...Vals>
		auto operator()(Vals... vals) const
		{
			using T = typename std::common_type<Vals...>::type;
			return std::array<T, sizeof...(Vals)> {vals...};
		}
	};

	struct XorOp : srp::Op<Concat, std::bit_xor<void>>
	{
		template <typename Pack>
		friend std::array<int, Pack::size> operator^(const Pack& pack, int val)
		{
			return srp::eval<XorOp>(pack, val);
		}
	};
}

TEST_CASE("custom_of with custom operator ^")
{
	auto xor_of = srp::make_custom_of<XorOp>();

	REQUIRE((xor_of(0, 1, 2, 3) ^ 1) == std::array {1, 0, 3, 2});
	REQUIRE((xor_of(0, 1, 2, 3, 4, 5) ^ 1) == std::array {1, 0, 3, 2, 5, 4});
}

namespace
{
	struct NegOp : srp::Op<Concat, std::logical_not<void>>
	{
		template <typename Pack>
		friend std::array<bool, Pack::size> operator!(const Pack& pack)
		{
			return srp::eval<NegOp>(pack);
		}
	};
}

TEST_CASE("custom_of with custom unary operator !")
{
	auto neg_of = srp::make_custom_of<NegOp>();

	REQUIRE(!neg_of(true, false) == std::array {false, true});
}

namespace
{
	template <typename T>
	struct identity
	{
		const T& operator()(const T& value) const { return value; }
	};

	template <typename ...Ops>
	struct Packer
	{
		constexpr static auto pack = srp::make_custom_of<Ops...>();

		template <typename ...Ts>
		auto operator()(const Ts&... values) const
		{
			return pack(values..., values...);
		}
	};

	struct ArrayOp : srp::Op<Concat, identity<int>>
	{
		template <typename Pack>
		friend auto to_array(const Pack& pack)
		{
			return srp::eval<ArrayOp>(pack);
		}
	};

	struct DoubleOp : srp::Op<Packer<DoubleOp, ArrayOp>, identity<int>>
	{
		template <typename Pack>
		friend auto operator!(const Pack& pack)
		{
			return srp::eval<DoubleOp>(pack);
		}
	};
}

TEST_CASE("custom_of with chained operator")
{
	auto double_of = srp::make_custom_of<DoubleOp, ArrayOp>();

	REQUIRE(to_array(!double_of(1, 2, 3)) == std::array {1, 2, 3,  1, 2, 3});
	REQUIRE(to_array(!!double_of(1, 2, 3)) == std::array {1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3});
	REQUIRE(to_array(!!!double_of(1, 2, 3)) == std::array {1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3,  1, 2, 3});
}
