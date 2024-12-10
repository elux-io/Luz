#pragma once

#include <concepts>
#include <limits>
#include <compare>

namespace lux::num::detail
{
	template<typename T>
	concept Arithmetic = std::floating_point<T> or std::integral<T>;
}

#define LUX_DEFINE_NUMBER(name, value) \
	namespace detail \
	{ \
		struct name##Number \
		{ \
			template<Arithmetic T> consteval operator T() const { return value; } \
			friend constexpr auto operator==(Arithmetic auto a, name##Number b) { return a == static_cast<decltype(a)>(b); } \
			friend constexpr auto operator==(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) == b; } \
			friend constexpr auto operator<=>(Arithmetic auto a, name##Number b) { return a <=> static_cast<decltype(a)>(b); } \
			friend constexpr auto operator<=>(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) <=> b; } \
			friend constexpr auto operator+(Arithmetic auto a, name##Number b) { return a + static_cast<decltype(a)>(b); } \
			friend constexpr auto operator+(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) + b; } \
			friend constexpr auto operator-(Arithmetic auto a, name##Number b) { return a - static_cast<decltype(a)>(b); } \
			friend constexpr auto operator-(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) - b; } \
			friend constexpr auto operator*(Arithmetic auto a, name##Number b) { return a * static_cast<decltype(a)>(b); } \
			friend constexpr auto operator*(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) * b; } \
			friend constexpr auto operator/(Arithmetic auto a, name##Number b) { return a / static_cast<decltype(a)>(b); } \
			friend constexpr auto operator/(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) / b; } \
			friend constexpr auto operator%(Arithmetic auto a, name##Number b) { return a % static_cast<decltype(a)>(b); } \
			friend constexpr auto operator%(name##Number a, Arithmetic auto b) { return static_cast<decltype(b)>(a) % b; } \
			template<Arithmetic A> friend constexpr auto& operator+=(A& a, name##Number b) { return a += static_cast<A>(b); } \
			template<Arithmetic A> friend constexpr auto& operator-=(A& a, name##Number b) { return a -= static_cast<A>(b); } \
			template<Arithmetic A> friend constexpr auto& operator*=(A& a, name##Number b) { return a *= static_cast<A>(b); } \
			template<Arithmetic A> friend constexpr auto& operator/=(A& a, name##Number b) { return a /= static_cast<A>(b); } \
			template<Arithmetic A> friend constexpr auto& operator%=(A& a, name##Number b) { return a %= static_cast<A>(b); } \
		}; \
	} \
	inline constexpr auto name = detail::name##Number()

namespace lux::num
{
    LUX_DEFINE_NUMBER(E,     T(2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274));
    LUX_DEFINE_NUMBER(Phi,   T(1.6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374));
    LUX_DEFINE_NUMBER(Pi,    T(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679));
    LUX_DEFINE_NUMBER(Sqrt2, T(1.4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727));
    LUX_DEFINE_NUMBER(Tau,   T(6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341359));

    LUX_DEFINE_NUMBER(Epsilon, std::numeric_limits<T>::epsilon());
    LUX_DEFINE_NUMBER(Infinity, std::numeric_limits<T>::infinity());
    LUX_DEFINE_NUMBER(Lowest, std::numeric_limits<T>::lowest());
    LUX_DEFINE_NUMBER(Max, std::numeric_limits<T>::max());
    LUX_DEFINE_NUMBER(Min, std::numeric_limits<T>::min());
}

#undef LUX_DEFINE_NUMBER
