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
struct Values;

template <std::size_t ...Idxs, typename ...Ts>
struct Values<std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	template <typename T>
	friend bool __attribute__((always_inline)) operator==(const Values& values, const T& value)
	{
		return ((value == values.Value<Idxs, T>::value) || ...);
	}

	template <typename T>
	friend bool __attribute__((always_inline)) operator==(const T& value, const Values& values)
	{
		return values == value;
	}
};

template <typename ...Ts>
auto any_of(const Ts&... vals)
{
	return Values<std::index_sequence_for<Ts...>, Ts...> {{vals}...};
}

}
