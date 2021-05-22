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
	Value(const T& value) : value {value}
	{}

	const T& get() const { return value; }

private:
	const T& value;
};

template <class Idxs, class ...Ts>
struct Values;

template <size_t ...Idxs, typename ...Ts>
struct Values<std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	Values(const Ts&... vs) : Value<Idxs, Ts>(vs)...
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
auto any_of(const Ts&... vals)
{
	return Values<std::index_sequence_for<Ts...>, Ts...> (vals...);
}

}
