#pragma once

#include "PlatformMacros.hpp"

#if LUZ_COMPILER(MSVC)
	#define LUZ_DEBUG_BREAK() (__debugbreak())
#elif LUZ_COMPILER(CLANG) or LUZ_COMPILER(GCC)
	#define LUZ_DEBUG_BREAK() (__builtin_trap())
#else
	#define LUZ_DEBUG_BREAK() ((void)0)
#endif

#if not defined(NDEBUG)
	#define LUZ_ASSERT(expr, ...) ((expr) or (LUZ_DEBUG_BREAK(), false))
#else
	#define LUZ_ASSERT(...) ((void)0)
#endif

namespace luz
{
	[[noreturn]] inline auto Unreachable() -> void
	{
		#if LUZ_COMPILER(MSVC)
			__assume(false);
		#elif LUZ_COMPILER(CLANG) or LUZ_COMPILER(GCC)
			__builtin_unreachable();
		#endif
	}
}
