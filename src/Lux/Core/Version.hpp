#pragma once

#include "Types.hpp"

#include <compare>

namespace lux
{
	struct Version
	{
		u32 major;
		u32 minor;
		u32 patch;

		constexpr auto operator<=>(Version const&) const = default;
	};

	consteval auto GetVersion() { return Version { 0, 0, 1 }; }
}
