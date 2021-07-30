#ifndef SRP_ANY_OF_HPP
#define SRP_ANY_OF_HPP

#ifndef SRP_ATTR_FORCE_INLINE
#define SRP_ATTR_FORCE_INLINE __attribute__((always_inline))
#endif

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

template <typename ...Ops>
struct OpList : Ops... {};

template <class Ops, class Idxs, class ...Ts>
struct Pack;

template <typename ...Ops, std::size_t ...Idxs, typename ...Ts>
struct Pack<OpList<Ops...>, std::index_sequence<Idxs...>, Ts...> : OpList<Ops...>, Value<Idxs, Ts>...
{
	constexpr static std::size_t size = sizeof...(Ts);
};

template <typename Reducer, typename Mapper>
struct Op
{
	[[no_unique_address]] Reducer reduce;
	[[no_unique_address]] Mapper map;

	template <typename T, typename Ops, std::size_t ...Idxs, typename ...Ts>
	auto SRP_ATTR_FORCE_INLINE eval(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack, const T& value) const
	{
		return reduce(map(value, pack.Value<Idxs, Ts>::value)...);
	}

	template <typename T, typename Ops, std::size_t ...Idxs, typename ...Ts>
	auto SRP_ATTR_FORCE_INLINE eval(const T& value, const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack) const
	{
		return eval(pack, value);
	}

	template <typename Ops, std::size_t ...Idxs, typename ...Ts>
	auto SRP_ATTR_FORCE_INLINE eval(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack) const
	{
		return reduce(map(pack.Value<Idxs, Ts>::value)...);
	}
};

template <typename Op, typename Ops, typename T, std::size_t ...Idxs, typename ...Ts>
auto SRP_ATTR_FORCE_INLINE eval(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack, const T& value)
{
	return static_cast<const Op&>(pack).eval(pack, value);
}
template <typename Op, typename Ops, typename T, std::size_t ...Idxs, typename ...Ts>
auto SRP_ATTR_FORCE_INLINE eval(const T& value, const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
{
	return static_cast<const Op&>(pack).eval(pack, value);
}
template <typename Op, typename Ops, std::size_t ...Idxs, typename ...Ts>
auto SRP_ATTR_FORCE_INLINE eval(const Pack<Ops, std::index_sequence<Idxs...>, Ts...>& pack)
{
	return static_cast<const Op&>(pack).eval(pack);
}

template <class Reducer, class Eq>
struct EqOp : Op<Reducer, Eq>
{
	template <typename PackOrValueA, typename PackOrValueB>
	friend bool SRP_ATTR_FORCE_INLINE operator==(const PackOrValueA& x, const PackOrValueB& y)
	{
		return eval<EqOp>(x, y);
	}
};

template <class Reducer, class Neq>
struct NeqOp : Op<Reducer, Neq>
{
	template <typename PackOrValueA, typename PackOrValueB>
	friend bool SRP_ATTR_FORCE_INLINE operator!=(const PackOrValueA& x, const PackOrValueB& y)
	{
		return eval<NeqOp>(x, y);
	}
};

template <typename ...Ops, typename ...Ts>
constexpr auto make_pack(const Ts&... values)
{
	return Pack<OpList<Ops...>, std::index_sequence_for<Ts...>, Ts...> {{}, {values}...};
}

template <typename ...Ops>
constexpr auto make_custom_of()
{
	return [](const auto& ...args) constexpr
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

#endif
