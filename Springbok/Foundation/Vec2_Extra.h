#pragma once

#include <ostream>

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Vec2<T>& obj)
{
	return stream << "(" << obj.X << "," << obj.Y << ")";
}

// UGH... TODO: Remove, replace (would break testing)
template<typename T, typename P>
constexpr bool operator>(const Vec2<T>& a, const Vec2<P>& b)
{
	return (a.X + a.Y * 8) > (b.X + b.Y * 8);
};

template<typename T, typename P>
constexpr bool operator<(const Vec2<T>& a, const Vec2<P>& b)
{
	return (a.X + a.Y * 8) < (b.X + b.Y * 8);
};