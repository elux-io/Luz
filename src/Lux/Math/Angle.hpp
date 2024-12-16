#pragma once

#include "Numbers.hpp"

#include <concepts>
#include <array>
#include <cmath>
#include <compare>

namespace lux
{
	enum class AngularUnit
	{
		Turn,
		Radian,
		Degree,
		Gon,
	};

	namespace detail
	{
		template<std::floating_point T>
		constexpr auto ConversionFactors = std::array {
		               // from \ to   Turn               Radian               Degree              Gon
			std::array /* Turn */   { T(1),              T(num::Tau),         T(360),             T(400) },
			std::array /* Radian */ { T(1.l / num::Tau), T(1),                T(180.l / num::Pi), T(400.l / num::Tau) },
			std::array /* Degree */ { T(1.l / 360.l),    T(num::Pi / 180.l),  T(1),               T(400.l / 360.l) },
			std::array /* Gon */    { T(1.l / 400.l),    T(num::Tau / 400.l), T(360.l / 400.l),   T(1) },
		};

		template<AngularUnit from, AngularUnit to, std::floating_point T>
		constexpr auto Convert(T angle) -> T
		{
			if constexpr (from == to)
				return angle;
			else
				return angle * ConversionFactors<T>[static_cast<std::size_t>(from)][static_cast<std::size_t>(to)];
		}
	}

	template<AngularUnit unit, std::floating_point T>
	class Angle
	{
	public:
		constexpr Angle() = default;
		constexpr Angle(T value) : m_value(value) {}
		template<AngularUnit fromUnit> constexpr Angle(Angle<fromUnit, T> angle) : m_value(detail::Convert<fromUnit, unit>(angle.Get())) {}

		// TODO: constexpr + optimize for turns??
		auto Sin() const { return std::sin(ToRadians().Get()); }
		auto Cos() const { return std::cos(ToRadians().Get()); }
		auto Tan() const { return std::tan(ToRadians().Get()); }

		constexpr auto ToTurns() const { return Angle<AngularUnit::Turn, T>(*this); }
		constexpr auto ToDegrees() const { return Angle<AngularUnit::Degree, T>(*this); }
		constexpr auto ToRadians() const { return Angle<AngularUnit::Radian, T>(*this); }
		constexpr auto ToGons() const { return Angle<AngularUnit::Gon, T>(*this); }
		constexpr auto Get() const { return m_value; }

		constexpr auto& operator+=(Angle b) { m_value += b.m_value; return *this; }
		constexpr auto& operator-=(Angle b) { m_value -= b.m_value; return *this; }
		constexpr auto& operator*=(Angle b) { m_value *= b.m_value; return *this; }
		constexpr auto& operator/=(Angle b) { m_value /= b.m_value; return *this; }

		friend constexpr auto operator<=>(Angle a, Angle b) = default;

		friend constexpr auto operator-(Angle a) { return Angle(-a.m_value); }

		friend constexpr auto operator+(Angle a, Angle b) { return a += b; }
		friend constexpr auto operator-(Angle a, Angle b) { return a -= b; }
		friend constexpr auto operator*(Angle a, Angle b) { return a *= b; }
		friend constexpr auto operator/(Angle a, Angle b) { return a /= b; }

	private:
		T m_value;
	};

	using Turns = Angle<AngularUnit::Turn, float>;
	using Degrees = Angle<AngularUnit::Degree, float>;
	using Radians = Angle<AngularUnit::Radian, float>;
	using Gons = Angle<AngularUnit::Gon, float>;

	namespace literals
	{
		consteval auto operator""_turn(long double value) { return Turns(static_cast<float>(value)); }
		consteval auto operator""_deg(long double value) { return Degrees(static_cast<float>(value)); }
		consteval auto operator""_rad(long double value) { return Radians(static_cast<float>(value)); }
		consteval auto operator""_gon(long double value) { return Gons(static_cast<float>(value)); }
	}
}
