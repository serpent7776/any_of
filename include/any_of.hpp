#include <utility>

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

template <class Idxs, class ...Ts>
struct Pack;

template <std::size_t ...Idxs, typename ...Ts>
struct Pack<std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	template <typename T>
	friend bool __attribute__((always_inline)) operator==(const Pack& pack, const T& value)
	{
		return ((value == pack.Value<Idxs, Ts>::value) || ...);
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
	return Pack<std::index_sequence_for<Ts...>, Ts...> {{vals}...};
}

}
