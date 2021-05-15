#include <utility>

namespace srp
{

template <typename T, typename ...Ts>
bool equals_to_any_of(T&& val, Ts&&... vals)
{
	return ((val == vals) || ...);
}

template <size_t, typename T>
class Value
{
public:
	Value(T&& value) : value {std::forward<T>(value)}
	{}

	const T& get() const { return value; }

private:
	T value;
};

template <class Idxs, class ...Ts>
struct Values;

template <size_t ...Idxs, typename ...Ts>
struct Values<std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	Values(Ts&&... vs) : Value<Idxs, Ts>(std::forward<Ts>(vs))...
	{}

	template <typename T>
	bool operator==(const T& value) const
	{
		return ((value == Value<Idxs, Ts>::get()) || ...);
	}
};

template <typename T, typename Idx, typename ...Ts>
bool operator==(const T& value, const Values<Idx, Ts...>& values)
{
	return values == value;
}

template <typename ...Ts>
auto any_of(Ts&&... vals)
{
	return Values<std::index_sequence_for<Ts...>, Ts...> (std::forward<Ts>(vals)...);
}

}
