#include <utility>
#include <functional>

namespace srp
{

template <typename T, typename ...Ts>
bool equals_to_any_of(T&& val, Ts&&... vals)
{
	return ((val == vals) || ...);
}

struct logical_or
{
	template<typename ...Ts>
	auto operator()(const Ts&... args) const
	{
		return (args || ...);
	}
};

struct logical_and
{
	template<typename ...Ts>
	auto operator()(const Ts&... args) const
	{
		return (args && ...);
	}
};

struct only_one
{
	template<typename ...Ts>
	auto operator()(const Ts&... args) const
	{
		return ((bool)args + ...) == 1;
	}
};

template <std::size_t, typename T>
struct Value
{
	const T& value;
};

template <class Reducer, class Eq>
struct EqOp
{
	[[no_unique_address]] Reducer reducer;
	[[no_unique_address]] Eq eq;

	template <template <typename, typename, typename, typename...> class Pack, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator==(const Pack<Reducer, Eq, std::index_sequence<Idxs...>, Ts...>& pack, const T& value)
	{
		const Reducer& reducer = pack.EqOp<Reducer, Eq>::reducer;
		const Eq& eq = pack.EqOp<Reducer, Eq>::eq;
		return reducer(eq(value, pack.Value<Idxs, Ts>::value)...);
	}

	template <template <typename, typename, typename, typename...> class Pack, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator==(const T& value, const Pack<Reducer, Eq, std::index_sequence<Idxs...>, Ts...>& pack)
	{
		return pack == value;
	}
};

template <class Reducer, class Eq, class Idxs, class ...Ts>
struct Pack;

template <class Reducer, class Eq, std::size_t ...Idxs, typename ...Ts>
struct Pack<Reducer, Eq, std::index_sequence<Idxs...>, Ts...> : EqOp<Reducer, Eq>, Value<Idxs, Ts>...
{
};

template <typename ReduceOp, typename EqOp, typename ...Ts>
auto make_pack(const Ts&... values)
{
	return Pack<ReduceOp, EqOp, std::index_sequence_for<Ts...>, Ts...> {{}, {values}...};
}

template <typename ...Ts>
auto any_of(const Ts&... vals)
{
	return make_pack<logical_or, std::equal_to<void>>(vals...);
}

template <typename ...Ts>
auto none_of(const Ts&... vals)
{
	return make_pack<logical_and, std::not_equal_to<void>>(vals...);
}

template <typename ...Ts>
auto all_of(const Ts&... vals)
{
	return make_pack<logical_and, std::equal_to<void>> (vals...);
}

template <typename ...Ts>
auto one_of(const Ts&... vals)
{
	return make_pack<only_one, std::equal_to<void>>(vals...);
}

}
