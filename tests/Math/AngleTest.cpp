#include <Lux/Math/Angle.hpp>
#include <Lux/Math/Numbers.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <type_traits>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

TEST_CASE("Angle", "[Math]")
{
	SECTION("ctor")
	{
		CHECK(lux::Angle<lux::AngularUnit::Turn, float>().Get() == 0.f);
		CHECK(lux::Angle<lux::AngularUnit::Turn, float>(1.f).Get() == 1.f);
		CHECK(lux::Angle<lux::AngularUnit::Degree, float>(1.f).Get() == 1.f);

		// T must be the same
		STATIC_CHECK(std::is_constructible_v<lux::Angle<lux::AngularUnit::Turn, float>, lux::Angle<lux::AngularUnit::Degree, float>>);
		STATIC_CHECK_FALSE(std::is_constructible_v<lux::Angle<lux::AngularUnit::Turn, double>, lux::Angle<lux::AngularUnit::Turn, float>>);

		// implicit construction from T or Angle
		STATIC_CHECK(std::is_convertible_v<float, lux::Angle<lux::AngularUnit::Turn, float>>);
		STATIC_CHECK(std::is_convertible_v<lux::Angle<lux::AngularUnit::Degree, float>, lux::Angle<lux::AngularUnit::Turn, float>>);
	}

	SECTION("trigonometric functions")
	{
		using A = lux::Angle<lux::AngularUnit::Turn, float>;

		CHECK_THAT(A(1.f).Sin(), WithinAbs(0.f, 1e-6f));
		CHECK_THAT(A(1.f).Cos(), WithinRel(1.f));
		CHECK_THAT(A(1.f).Tan(), WithinAbs(0.f, 1e-6f));
	}

	SECTION("conversions")
	{
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK(a.ToTurns().Get() == 1.f);
			CHECK_THAT(a.ToRadians().Get(), WithinRel(float(lux::num::Tau)));
			CHECK_THAT(a.ToDegrees().Get(), WithinRel(360.f));
			CHECK_THAT(a.ToGons().Get(), WithinRel(400.f));
		}

		{
			auto const a = lux::Angle<lux::AngularUnit::Radian, float>(lux::num::Tau);
			CHECK_THAT(a.ToTurns().Get(), WithinRel(1.f));
			CHECK(a.ToRadians().Get() == lux::num::Tau);
			CHECK_THAT(a.ToDegrees().Get(), WithinRel(360.f));
			CHECK_THAT(a.ToGons().Get(), WithinRel(400.f));
		}

		{
			auto const a = lux::Angle<lux::AngularUnit::Degree, float>(360.f);
			CHECK_THAT(a.ToTurns().Get(), WithinRel(1.f));
			CHECK_THAT(a.ToRadians().Get(), WithinRel(float(lux::num::Tau)));
			CHECK(a.ToDegrees().Get() == 360.f);
			CHECK_THAT(a.ToGons().Get(), WithinRel(400.f));
		}

		{
			auto const a = lux::Angle<lux::AngularUnit::Gon, float>(400.f);
			CHECK_THAT(a.ToTurns().Get(), WithinRel(1.f));
			CHECK_THAT(a.ToRadians().Get(), WithinRel(float(lux::num::Tau)));
			CHECK_THAT(a.ToDegrees().Get(), WithinRel(360.f));
			CHECK(a.ToGons().Get() == 400.f);
		}
	}

	SECTION("operators")
	{
		// +=
		{
			auto a = lux::Angle<lux::AngularUnit::Turn, float>();
			a += lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK(a.Get() == 1.f);
		}

		// -=
		{
			auto a = lux::Angle<lux::AngularUnit::Turn, float>(2.f);
			a -= lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK(a.Get() == 1.f);
		}

		// *=
		{
			auto a = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			a *= lux::Angle<lux::AngularUnit::Turn, float>(2.f);
			CHECK(a.Get() == 2.f);
		}

		// /=
		{
			auto a = lux::Angle<lux::AngularUnit::Turn, float>(4.f);
			a /= lux::Angle<lux::AngularUnit::Turn, float>(2.f);
			CHECK(a.Get() == 2.f);
		}

		// <=>
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			auto const b = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK(a <=> b == std::partial_ordering::equivalent);
			CHECK(a == b);
			CHECK_FALSE(a != b);
			CHECK_FALSE(a < b);
			CHECK_FALSE(a > b);
			CHECK(a <= b);
			CHECK(a >= b);
		}

		// +
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>();
			auto const b = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK((a + b).Get() == 1.f);
		}

		// -
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>();
			auto const b = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			CHECK((-b).Get() == -1.f);
			CHECK((a - b).Get() == -1.f);
		}

		// *
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>(1.f);
			auto const b = lux::Angle<lux::AngularUnit::Turn, float>(2.f);
			CHECK((a * b).Get() == 2.f);
		}

		// /
		{
			auto const a = lux::Angle<lux::AngularUnit::Turn, float>(8.f);
			auto const b = lux::Angle<lux::AngularUnit::Turn, float>(2.f);
			CHECK((a / b).Get() == 4.f);
		}
	}

	SECTION("les opérateurs marchent avec un Angle ou un T à gauche ou à droite")
	{
		using A = lux::Angle<lux::AngularUnit::Turn, float>;

		CHECK((A(1.f) += 1.f).Get() == 2.f);
		CHECK((A(1.f) -= 1.f).Get() == 0.f);
		CHECK((A(1.f) *= 2.f).Get() == 2.f);
		CHECK((A(2.f) /= 1.f).Get() == 2.f);

		CHECK(A(1.f) <=> 1.f == std::partial_ordering::equivalent);
		CHECK(1.f <=> A(1.f) == std::partial_ordering::equivalent);

		CHECK((A(1.f) + 1.f).Get() == 2.f);
		CHECK((1.f + A(1.f)).Get() == 2.f);

		CHECK((A(1.f) - 1.f).Get() == 0.f);
		CHECK((1.f - A(1.f)).Get() == 0.f);

		CHECK((A(1.f) * 2.f).Get() == 2.f);
		CHECK((1.f * A(2.f)).Get() == 2.f);

		CHECK((A(2.f) / 1.f).Get() == 2.f);
		CHECK((2.f / A(1.f)).Get() == 2.f);
	}

	SECTION("aliases")
	{
		STATIC_CHECK(std::is_same_v<lux::Turns, lux::Angle<lux::AngularUnit::Turn, float>>);
		STATIC_CHECK(std::is_same_v<lux::Degrees, lux::Angle<lux::AngularUnit::Degree, float>>);
		STATIC_CHECK(std::is_same_v<lux::Radians, lux::Angle<lux::AngularUnit::Radian, float>>);
		STATIC_CHECK(std::is_same_v<lux::Gons, lux::Angle<lux::AngularUnit::Gon, float>>);
	}

	SECTION("literals")
	{
		using namespace lux::literals;

		STATIC_CHECK(std::is_same_v<decltype(1.0_turn), lux::Angle<lux::AngularUnit::Turn, float>>);
		STATIC_CHECK(std::is_same_v<decltype(1.0_deg), lux::Angle<lux::AngularUnit::Degree, float>>);
		STATIC_CHECK(std::is_same_v<decltype(1.0_rad), lux::Angle<lux::AngularUnit::Radian, float>>);
		STATIC_CHECK(std::is_same_v<decltype(1.0_gon), lux::Angle<lux::AngularUnit::Gon, float>>);
	}

	SECTION("constexpr")
	{
		using A = lux::Angle<lux::AngularUnit::Turn, float>;
		using B = lux::Angle<lux::AngularUnit::Degree, float>;

		STATIC_CHECK(A().Get() == 0.f);
		STATIC_CHECK(A(1.f).Get() == 1.f);
		STATIC_CHECK(A(B()) == 0.f);

		STATIC_CHECK(A().ToTurns().Get() == 0.f);
		STATIC_CHECK(A().ToDegrees().Get() == 0.f);
		STATIC_CHECK(A().ToRadians().Get() == 0.f);
		STATIC_CHECK(A().ToGons().Get() == 0.f);

		[]() consteval {
			auto a = A();
			a += 0.f;
			a -= 0.f;
			a *= 0.f;
			a /= 1.f;
		}();

		STATIC_CHECK(A() <=> A() == std::partial_ordering::equivalent);
		STATIC_CHECK((-A()).Get() == 0.f);
		STATIC_CHECK((A() + A()).Get() == 0.f);
		STATIC_CHECK((A() - A()).Get() == 0.f);
		STATIC_CHECK((A() * A()).Get() == 0.f);
		STATIC_CHECK((A() / A(1.f)).Get() == 0.f);
	}
}
