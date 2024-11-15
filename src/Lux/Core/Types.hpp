#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace lux
{
	using u8  = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8  = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	namespace literals
	{
		consteval auto operator""_u8(unsigned long long v) { return static_cast<u8>(v); }
		consteval auto operator""_u16(unsigned long long v) { return static_cast<u16>(v); }
		consteval auto operator""_u32(unsigned long long v) { return static_cast<u32>(v); }
		consteval auto operator""_u64(unsigned long long v) { return static_cast<u64>(v); }

		consteval auto operator""_i8(unsigned long long v) { return static_cast<i8>(v); }
		consteval auto operator""_i16(unsigned long long v) { return static_cast<i16>(v); }
		consteval auto operator""_i32(unsigned long long v) { return static_cast<i32>(v); }
		consteval auto operator""_i64(unsigned long long v) { return static_cast<i64>(v); }

		consteval auto operator""_z(unsigned long long v) { return static_cast<std::make_signed_t<std::size_t>>(v); }
		consteval auto operator""_zu(unsigned long long v) { return static_cast<std::size_t>(v); }
	}
}
