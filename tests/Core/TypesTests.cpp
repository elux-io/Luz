#include <Luz/Core/Types.hpp>
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("Types", "[Core]")
{
	SECTION("size")
	{
		STATIC_CHECK(sizeof(luz::u8) == 1);
		STATIC_CHECK(sizeof(luz::u16) == 2);
		STATIC_CHECK(sizeof(luz::u32) == 4);
		STATIC_CHECK(sizeof(luz::u64) == 8);

		STATIC_CHECK(sizeof(luz::i8) == 1);
		STATIC_CHECK(sizeof(luz::i16) == 2);
		STATIC_CHECK(sizeof(luz::i32) == 4);
		STATIC_CHECK(sizeof(luz::i64) == 8);
	}

	SECTION("literals")
	{
		using namespace luz::literals;

		constexpr auto u8 = 0_u8;
		constexpr auto u16 = 0_u16;
		constexpr auto u32 = 0_u32;
		constexpr auto u64 = 0_u64;

		STATIC_CHECK(std::is_same_v<decltype(u8), luz::u8 const>);
		STATIC_CHECK(std::is_same_v<decltype(u16), luz::u16 const>);
		STATIC_CHECK(std::is_same_v<decltype(u32), luz::u32 const>);
		STATIC_CHECK(std::is_same_v<decltype(u64), luz::u64 const>);

		constexpr auto i8 = 0_i8;
		constexpr auto i16 = 0_i16;
		constexpr auto i32 = 0_i32;
		constexpr auto i64 = 0_i64;

		STATIC_CHECK(std::is_same_v<decltype(i8), luz::i8 const>);
		STATIC_CHECK(std::is_same_v<decltype(i16), luz::i16 const>);
		STATIC_CHECK(std::is_same_v<decltype(i32), luz::i32 const>);
		STATIC_CHECK(std::is_same_v<decltype(i64), luz::i64 const>);

		constexpr auto z = 0_z;
		constexpr auto zu = 0_zu;

		STATIC_CHECK(std::is_same_v<decltype(z), std::make_signed_t<std::size_t> const>);
		STATIC_CHECK(std::is_same_v<decltype(zu), std::size_t const>);
	}
}
