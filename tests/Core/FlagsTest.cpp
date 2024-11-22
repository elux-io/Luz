#include "../Utils.hpp"

#include <Lux/Core/Flags.hpp>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

enum class Flag
{
	A = 1,
	B = 2,
	C = 4,
	D = B | C
};

LUX_ENABLE_FLAGS(Flag, { .isPow2 = true });

enum class FlagNPOT
{
	A,
	B,
	C,
	D
};

LUX_ENABLE_FLAGS(FlagNPOT, { .isPow2 = false });

// oui on peut "activer les flags" pour une struct mais ça se fera rejeter plus tard
// don't worry chat
struct S {};
LUX_ENABLE_FLAGS(S, {});

TEST_CASE("Flags", "[Core]")
{
	SECTION("ne fonctionne que sur les enums et avec les flags activés")
	{
		enum class E {};

		[]<typename T, typename U, typename V> {
			CHECK_DOES_NOT_COMPILE(lux::Flags<T>());
			CHECK_DOES_NOT_COMPILE(lux::Flags<U>());
			CHECK_DOES_NOT_COMPILE(lux::Flags<V>());
		}.operator()<S, int, E>();
	}

	SECTION("ctor")
	{
		// default
		CHECK(lux::Flags<Flag>().GetBits() == 0);

		// from enum
		CHECK(lux::Flags(Flag::B).GetBits() == 0b10);
		CHECK(lux::Flags(FlagNPOT::B).GetBits() == 0b10);

		// from bits
		{
			using F = lux::Flags<Flag>;

			auto const a = F(0b1); // ok, explicit
			CHECK(a.GetBits() == 0b1);

			// but implicit isn't allowed
			STATIC_CHECK_FALSE(std::is_convertible_v<F::Bits, F>);
		}
	}

	SECTION("Has")
	{
		{
			auto const a = lux::Flags(Flag::A);
			CHECK(a.Has(Flag::A));
			CHECK((a | Flag::B).Has(Flag::A | Flag::B));
			CHECK_FALSE(a.Has(Flag::B));
		}

		{
			auto const a = FlagNPOT::A | FlagNPOT::B | FlagNPOT::C;
			CHECK(a.Has(FlagNPOT::B));
			CHECK_FALSE(a.Has(FlagNPOT::D));
			CHECK((a | FlagNPOT::B).Has(FlagNPOT::A | FlagNPOT::B));
		}
	}

	SECTION("Set")
	{
		{
			auto a = lux::Flags<Flag>();
			a.Set(Flag::A);
			a.Set(Flag::B | Flag::C);
			CHECK(a.GetBits() == 0b111);
		}

		{
			auto a = lux::Flags<Flag>();
			a.Set(Flag::D);
			CHECK(a.GetBits() == 0b110);
		}

		{
			auto a = lux::Flags(FlagNPOT::A);
			a.Set(FlagNPOT::B);
			CHECK(a.GetBits() == 0b11);
		}
	}

	SECTION("Unset")
	{
		{
			auto a = Flag::A | Flag::C;
			a.Unset(Flag::A);
			a.Unset(Flag::B);
			CHECK(a.GetBits() == 0b100);
		}

		{
			auto a = FlagNPOT::A | FlagNPOT::C;
			a.Unset(FlagNPOT::A);
			a.Unset(FlagNPOT::B);
			CHECK(a.GetBits() == 0b100);
		}
	}

	SECTION("IsEmpty")
	{
		CHECK(lux::Flags<Flag>().IsEmpty());
		CHECK_FALSE(lux::Flags(Flag::A).IsEmpty());
	}

	SECTION("&")
	{
		{
			auto a = lux::Flags(Flag::D);
			a &= Flag::B;
			CHECK(a.GetBits() == 0b10);
			a &= Flag::B;
			CHECK(a.GetBits() == 0b10);

			CHECK((Flag::D & Flag::B).GetBits() == 0b10);
		}

		{
			auto a = FlagNPOT::A | FlagNPOT::B;
			a &= FlagNPOT::B;
			CHECK(a.GetBits() == 0b10);
			a &= FlagNPOT::B;
			CHECK(a.GetBits() == 0b10);

			CHECK(((FlagNPOT::A | FlagNPOT::B) & FlagNPOT::B).GetBits() == 0b10);
		}
	}

	SECTION("|")
	{
		{
			auto a = lux::Flags(Flag::A);
			a |= Flag::B;
			CHECK(a.GetBits() == 0b11);
			a |= Flag::B;
			CHECK(a.GetBits() == 0b11);

			CHECK((Flag::A | Flag::B).GetBits() == 0b11);
		}

		{
			auto a = lux::Flags(FlagNPOT::A);
			a |= FlagNPOT::B;
			CHECK(a.GetBits() == 0b11);
			a |= FlagNPOT::B;
			CHECK(a.GetBits() == 0b11);

			CHECK((FlagNPOT::A | FlagNPOT::B).GetBits() == 0b11);
		}
	}

	SECTION("^")
	{
		{
			auto a = Flag::A | Flag::B;
			a ^= Flag::B;
			CHECK(a.GetBits() == 0b01);

			CHECK(((Flag::A | Flag::B) ^ Flag::B).GetBits() == 0b01);
		}

		{
			auto a = FlagNPOT::A | FlagNPOT::B;
			a ^= FlagNPOT::B;
			CHECK(a.GetBits() == 0b01);

			CHECK(((FlagNPOT::A | FlagNPOT::B) ^ FlagNPOT::B).GetBits() == 0b01);
		}
	}

	SECTION("constexpr")
	{
		constexpr auto a = lux::Flags(Flag::A);
		constexpr auto b = lux::Flags<Flag>();
		constexpr auto c = lux::Flags<Flag>(0b1);

		STATIC_CHECK(a.Has(Flag::A));
		STATIC_CHECK([] {
			auto a = lux::Flags<Flag>();
			a.Set(Flag::A);
			return a;
		}().GetBits() == 0b1);
		STATIC_CHECK([] {
			auto a = lux::Flags(Flag::A);
			a.Unset(Flag::A);
			return a;
		}().GetBits() == 0);
		STATIC_CHECK(b.IsEmpty());
		STATIC_CHECK(c.GetBits() == 0b1);

		STATIC_CHECK((lux::Flags(Flag::A) &= Flag::B).GetBits() == 0);
		STATIC_CHECK((lux::Flags(Flag::A) |= Flag::B).GetBits() == 0b11);
		STATIC_CHECK((lux::Flags(Flag::A) ^= Flag::B).GetBits() == 0b11);

		STATIC_CHECK(a == Flag::A);
		STATIC_CHECK(a != Flag::B);

		STATIC_CHECK((a & Flag::B).GetBits() == 0);
		STATIC_CHECK((a | Flag::B).GetBits() == 0b11);
		STATIC_CHECK((a ^ Flag::B).GetBits() == 0b11);

		STATIC_CHECK((Flag::A & Flag::B).GetBits() == 0);
		STATIC_CHECK((Flag::A | Flag::B).GetBits() == 0b11);
		STATIC_CHECK((Flag::A ^ Flag::B).GetBits() == 0b11);
	}

	SECTION("les opérateurs marchent avec l'enum directement ou avec des Flags, à droite ou à gauche")
	{
		CHECK(Flag::A == Flag::A);
		CHECK(lux::Flags(Flag::A) == Flag::A);
		CHECK(Flag::A == lux::Flags(Flag::A));
		CHECK(lux::Flags(Flag::A) == lux::Flags(Flag::A));

		CHECK(Flag::A != Flag::B);
		CHECK(lux::Flags(Flag::A) != Flag::B);
		CHECK(Flag::A != lux::Flags(Flag::B));
		CHECK(lux::Flags(Flag::A) != lux::Flags(Flag::B));

		CHECK((Flag::A & Flag::C).GetBits() == 0);
		CHECK((lux::Flags(Flag::A) & Flag::C).GetBits() == 0);
		CHECK((Flag::A & lux::Flags(Flag::C)).GetBits() == 0);
		CHECK((lux::Flags(Flag::A) & lux::Flags(Flag::C)).GetBits() == 0);

		CHECK((Flag::A | Flag::C).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) | Flag::C).GetBits() == 0b101);
		CHECK((Flag::A | lux::Flags(Flag::C)).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) | lux::Flags(Flag::C)).GetBits() == 0b101);

		CHECK((Flag::A ^ Flag::C).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) ^ Flag::C).GetBits() == 0b101);
		CHECK((Flag::A ^ lux::Flags(Flag::C)).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) ^ lux::Flags(Flag::C)).GetBits() == 0b101);

		CHECK((lux::Flags(Flag::A) &= Flag::C).GetBits() == 0);
		CHECK((lux::Flags(Flag::A) &= lux::Flags(Flag::C)).GetBits() == 0);

		CHECK((lux::Flags(Flag::A) |= Flag::C).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) |= lux::Flags(Flag::C)).GetBits() == 0b101);

		CHECK((lux::Flags(Flag::A) ^= Flag::C).GetBits() == 0b101);
		CHECK((lux::Flags(Flag::A) ^= lux::Flags(Flag::C)).GetBits() == 0b101);
	}

	SECTION("on ne peut pas convertir des Flags en enum")
	{
		STATIC_CHECK_FALSE(std::is_constructible_v<Flag, lux::Flags<Flag>>);
	}
}
