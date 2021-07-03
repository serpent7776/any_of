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

template <typename Type, Type Sum>
struct sum_is
{
	template<typename ...Ts>
	auto operator()(const Ts&... args) const
	{
		return (args + ...) == Sum;
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

	template <template <typename, typename, typename...> class Pack, typename Ops, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator==(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack, const T& value)
	{
		const Reducer& reducer = pack.EqOp<Reducer, Eq>::reducer;
		const Eq& eq = pack.EqOp<Reducer, Eq>::eq;
		return reducer(eq(value, pack.Value<Idxs, Ts>::value)...);
	}

	template <template <typename, typename, typename...> class Pack, typename Ops, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator==(const T& value, const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
	{
		return pack == value;
	}
};

template <class Reducer, class Neq>
struct NeqOp
{
	[[no_unique_address]] Reducer reducer;
	[[no_unique_address]] Neq neq;

	template <template <typename, typename, typename...> class Pack, typename Ops, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator!=(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack, const T& value)
	{
		const Reducer& reducer = pack.NeqOp<Reducer, Neq>::reducer;
		const Neq& neq = pack.NeqOp<Reducer, Neq>::neq;
		return reducer(neq(value, pack.Value<Idxs, Ts>::value)...);
	}

	template <template <typename, typename, typename...> class Pack, typename Ops, typename T, size_t ...Idxs, typename ...Ts>
	friend bool __attribute__((always_inline)) operator!=(const T& value, const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
	{
		return pack != value;
	}
};

template <typename ...Ops>
struct OpList : Ops... {};

template <class Ops, class Idxs, class ...Ts>
struct Pack;

template <typename ...Ops, std::size_t ...Idxs, typename ...Ts>
struct Pack<OpList<Ops...>, std::index_sequence<Idxs...>, Ts...> : OpList<Ops...>, Value<Idxs, Ts>...
{
};

template <typename ...Ops, typename ...Ts>
auto make_pack(const Ts&... values)
{
	return Pack<OpList<Ops...>, std::index_sequence_for<Ts...>, Ts...> {{}, {values}...};
}

template <typename ...Ops>
auto make_custom_of()
{
	return [](const auto& ...args)
	{
		return make_pack<Ops...>(args...);
	};
}

template <typename ...Ts>
auto any_of(const Ts&... vals)
{
	return make_pack<EqOp<logical_or, std::equal_to<void>>>(vals...);
}

template <typename ...Ts>
auto none_of(const Ts&... vals)
{
	return make_pack<EqOp<logical_and, std::not_equal_to<void>>>(vals...);
}

template <typename ...Ts>
auto all_of(const Ts&... vals)
{
	return make_pack<EqOp<logical_and, std::equal_to<void>>> (vals...);
}

template <typename ...Ts>
auto one_of(const Ts&... vals)
{
	return make_pack<EqOp<sum_is<int, 1>, std::equal_to<void>>>(vals...);
}

}
