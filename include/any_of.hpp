#include <utility>
#include <functional>

namespace srp
{

template <typename T, typename ...Ts>
bool equals_to_any_of(T&& val, Ts&&... vals)
{
	return ((val == vals) || ...);
}

template <std::size_t, typename T>
struct Value
{
	const T& value;
};

template <class EqOp, class Idxs, class ...Ts>
struct Pack;

template <class EqOp, std::size_t ...Idxs, typename ...Ts>
struct Pack<EqOp, std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	template <typename T>
	friend bool __attribute__((always_inline)) operator==(const Pack& pack, const T& value)
	{
		const auto eq = EqOp();
		return (eq(value, pack.Value<Idxs, Ts>::value) || ...);
	}

	template <typename T>
	friend bool __attribute__((always_inline)) operator==(const T& value, const Pack& pack)
	{
		return pack == value;
	}
};

template <typename ...Ts>
auto any_of(const Ts&... vals)
{
	return Pack<std::equal_to<void>, std::index_sequence_for<Ts...>, Ts...> {{vals}...};
}

}
