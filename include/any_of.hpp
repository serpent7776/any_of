#include <utility>

namespace srp
{

template <typename T, typename ...Ts>
bool equals_to_any_of(T&& val, Ts&&... vals)
{
	return ((val == vals) || ...);
}

template <std::size_t, typename T>
class Value
{
public:
	Value() = delete;
	Value(const Value&) = delete;
	Value(Value&&) = delete;
	Value(const T& value) : value {value}
	{}

	Value& operator=(const Value&) = delete;
	Value& operator=(Value&&) = delete;

	const T& get() const { return value; }

private:
	const T& value;
};

template <class Idxs, class ...Ts>
struct Values;

template <std::size_t ...Idxs, typename ...Ts>
struct Values<std::index_sequence<Idxs...>, Ts...> : Value<Idxs, Ts>...
{
	Values() = delete;
	Values(const Values&) = delete;
	Values(Values&&) = delete;
	Values(const Ts&... vs) : Value<Idxs, Ts>(vs)...
	{}

	Values& operator=(const Values&) = delete;
	Values& operator=(Values&&) = delete;

	template <typename T>
	bool __attribute__((always_inline)) operator==(const T& value) const
	{
		return ((value == Value<Idxs, Ts>::get()) || ...);
	}
};

template <typename T, typename Idx, typename ...Ts>
bool __attribute__((always_inline)) operator==(const T& value, const Values<Idx, Ts...>& values)
{
	return values == value;
}

template <typename ...Ts>
auto any_of(const Ts&... vals)
{
	return Values<std::index_sequence_for<Ts...>, Ts...> (vals...);
}

}
