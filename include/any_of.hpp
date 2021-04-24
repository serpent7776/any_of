template <typename T, typename ...Ts>
bool equals_to_any_of(T val, Ts... vals)
{
	return ((val == vals) || ...);
}
