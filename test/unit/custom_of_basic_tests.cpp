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

namespace
{
	template <typename NewOps, typename Ops, size_t ...Idxs, typename ...Ts>
	auto repack(const srp::Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
	{
		return srp::make_pack<NewOps>(pack.template Value<Idxs, Ts>::value...);
	}

	struct Reverser
	{
		template <typename Ops, size_t... Idxs, typename ...Ts>
		auto reverse(const srp::Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack) const
		{
			return pack;
		}
		template <typename Ops, typename X, typename ...Xs, size_t ...Idxs, typename ...Ts>
		auto reverse(const srp::Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack, const X& value, const Xs&... values) const
		{
			return reverse(srp::make_pack(value, pack.template Value<Idxs, Ts>::value...), values...);
		}
		template <typename T, typename ...Ts>
		auto operator()(const T& value, const Ts&... values) const
		{
			return reverse(srp::make_pack(value), values...);
		}
	};

	struct ReverseOp : srp::Op<Reverser, identity<int>>
	{
		template <typename Ops, std::size_t ...Idxs, typename ...Ts>
		friend auto operator!(const srp::Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
		{
			return repack<Ops>(srp::eval<ReverseOp>(pack));
		}
	};
}

TEST_CASE("custom_of reversing")
{
	auto reverse_of = srp::make_custom_of<ReverseOp, ArrayOp>();

	REQUIRE(to_array(!reverse_of(1, 2, 3, 4, 5)) == std::array {5, 4, 3, 2, 1});
}

namespace
{
	template <typename ValueType>
	struct Field
	{
		const char* name;
		ValueType value;
	};

	std::string to_string(char c)
	{
		return std::string(1, c);
	}
	std::string to_string(const char* s)
	{
		return std::string(s);
	}
	std::string quote(const std::string& s)
	{
		return '"' + s + '"';
	}

	template <typename T>
	struct always_false
	{
		static constexpr bool value = false;
	};

	template <typename T>
	constexpr bool always_fail() {static_assert(always_false<T>::value); return false;}

	template <typename T> constexpr bool needs_quoting = always_fail<T>();
	template <> constexpr bool needs_quoting<int> = false;
	template <> constexpr bool needs_quoting<char> = true;

	template <typename T>
	std::string to_quoted_string(const T& value)
	{
		using std::to_string;
		using ::to_string;
		const std::string s = to_string(value);
		if constexpr (needs_quoting<T>)
		{
			return quote(s);
		}
		return s;
	}

	struct Stringify
	{
		template<typename T>
		std::string operator()(const Field<T>& field) const
		{
			using std::to_string;
			using ::to_string;
			return quote(to_string(field.name)) + '=' + to_quoted_string(field.value);
		}
	};

	struct StrJoin
	{
		template<typename String, typename ...Strings>
		std::string operator()(const String& string, const Strings&... strings) const
		{
			return '{' + string + ((", " + strings) + ...) + '}';
		}
	};

	struct JsonOp : srp::Op<StrJoin, Stringify>
	{
		template <typename Ops, std::size_t ...Idxs, typename ...Ts>
		friend auto operator+(const srp::Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
		{
			return srp::eval<JsonOp>(pack);
		}
	};
}

TEST_CASE("custom_of generating JSON")
{
	auto json_of = srp::make_custom_of<JsonOp>();

	REQUIRE(+json_of(Field<int>{"x", 12}, Field<char>{"y", 'a'}) == std::string {R"({"x"=12, "y"="a"})"});
}
