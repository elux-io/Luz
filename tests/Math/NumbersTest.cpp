#include <Lux/Math/Numbers.hpp>
#include <Lux/Core/Types.hpp>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

using namespace lux::literals;

TEST_CASE("Numbers", "[Math]")
{
	SECTION("deduction from the left-hand side")
	{
		constexpr lux::u16 a = lux::num::Max;
		constexpr lux::i16 b = lux::num::Max;
		STATIC_CHECK(a == 65'535_u16);
		STATIC_CHECK(b == 32'767_i16);
	}

	SECTION("no ambiguity between an arithmetic type and something else")
	{
		struct S
		{
			static auto f(S) { return 1; }
			static auto f(float) { return 2; }
		};

		CHECK(S::f(lux::num::Pi) == 2);
	}

	SECTION("comparison operators")
	{
		STATIC_CHECK(0u == lux::num::Min);
		STATIC_CHECK(lux::num::Min == 0u);

		STATIC_CHECK(0u <=> lux::num::Min == std::strong_ordering::equal);
		STATIC_CHECK(lux::num::Min <=> 0u == std::strong_ordering::equal);

		// synthesized
		STATIC_CHECK(0 != lux::num::Min);
		STATIC_CHECK(0 < lux::num::Max);
		STATIC_CHECK(0 <= lux::num::Max);
		STATIC_CHECK(0 > lux::num::Min);
		STATIC_CHECK(0 >= lux::num::Min);
	}

	SECTION("arithmetic operators")
	{
		STATIC_CHECK(0u + lux::num::Min == lux::num::Min);
		STATIC_CHECK(lux::num::Min + 0 == lux::num::Min);

		STATIC_CHECK(0u - lux::num::Min == 0u);
		STATIC_CHECK(lux::num::Min - 0u == lux::num::Min);

		STATIC_CHECK(0u * lux::num::Min == 0u);
		STATIC_CHECK(lux::num::Min * 0u == 0u);

		STATIC_CHECK(0u / lux::num::Max == 0u);
		STATIC_CHECK(lux::num::Min / 1u == lux::num::Min);

		STATIC_CHECK(0u % lux::num::Max == 0u);
		STATIC_CHECK(lux::num::Min % 1u == 0u);

		[]() consteval {
			auto a = 0u;
			a += lux::num::Min;
			a -= lux::num::Min;
			a *= lux::num::Min;
			a /= lux::num::Max;
			a %= lux::num::Max;
		}();
	}
}
