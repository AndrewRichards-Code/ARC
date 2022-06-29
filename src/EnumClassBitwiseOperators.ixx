export module ARC:EnumClassBitwiseOperators;
import std.core;

export template<typename _Ty>
constexpr _Ty operator|(_Ty lhs, _Ty rhs)
{
	return static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) | static_cast<typename std::underlying_type<_Ty>::type>(rhs));
}
export template<typename _Ty>
constexpr _Ty operator&(_Ty lhs, _Ty rhs)
{
	return static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) & static_cast<typename std::underlying_type<_Ty>::type>(rhs));
}
export template<typename _Ty>
constexpr _Ty operator^(_Ty lhs, _Ty rhs)
{
	return static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) ^ static_cast<typename std::underlying_type<_Ty>::type>(rhs));
}
export template<typename _Ty>
constexpr _Ty operator~(_Ty rhs)
{
	return static_cast<_Ty>(~static_cast<typename std::underlying_type<_Ty>::type>(rhs));
}
export template<typename _Ty>
constexpr _Ty& operator|=(_Ty& lhs, _Ty rhs)
{
	lhs = static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) | static_cast<typename std::underlying_type<_Ty>::type>(rhs));
	return lhs;
}
export template<typename _Ty>
constexpr _Ty& operator&=(_Ty& lhs, _Ty rhs)
{
	lhs = static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) & static_cast<typename std::underlying_type<_Ty>::type>(rhs));
	return lhs;
}
export template<typename _Ty>
constexpr _Ty& operator^=(_Ty& lhs, _Ty rhs)
{
	lhs = static_cast<_Ty>(static_cast<typename std::underlying_type<_Ty>::type>(lhs) ^ static_cast<typename std::underlying_type<_Ty>::type>(rhs));
	return lhs;
}