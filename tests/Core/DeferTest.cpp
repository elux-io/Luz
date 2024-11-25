#include "../Utils.hpp"

#include <Lux/Core/Defer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("Defer", "[Core]")
{
	SECTION("ça ne marche qu'avec des fonctions (sans paramètre)")
	{
		[]<typename T = int> {
			CHECK_DOES_NOT_COMPILE(lux::Deferrer(T()));
		}();

		[]<typename T = decltype([](int) {})> {
			CHECK_DOES_NOT_COMPILE(lux::Deferrer(T()));
		}();
	}

	SECTION("basic expression")
	{
		auto a = 0;

		{
			LUX_DEFER(a = 1);
			CHECK(a == 0);
		}

		CHECK(a == 1);
	}

	SECTION("on peut mettre des virgules")
	{
		auto a = false;

		{
			LUX_DEFER(a = std::is_same_v<int, int>);
			CHECK_FALSE(a);
		}

		CHECK(a);
	}

	SECTION("on peut passer un bloc")
	{
		auto a = 0;

		{
			LUX_DEFER({
				a = 1;
				a = 2;
			});
			CHECK(a == 0);
		}

		CHECK(a == 2);
	}

	SECTION("constexpr")
	{
		auto f = [] {
			auto a = 0;

			{
				auto d = lux::Deferrer([&] { a = 1; });
			}

			return a;
		};

		STATIC_CHECK(f() == 1);
	}
}
