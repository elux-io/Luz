#pragma once

#include "PlatformMacros.hpp"

#if LUX_COMPILER(MSVC)
	#define LUX_DEBUG_BREAK() (__debugbreak())
#elif LUX_COMPILER(CLANG) or LUX_COMPILER(GCC)
	#define LUX_DEBUG_BREAK() (__builtin_trap())
#else
	#define LUX_DEBUG_BREAK() ((void)0)
#endif

#if not defined(NDEBUG)
	#define LUX_ASSERT(expr, ...) ((expr) or (LUX_DEBUG_BREAK(), false))
#else
	#define LUX_ASSERT(...) ((void)0)
#endif

namespace lux
{
	[[noreturn]] inline auto Unreachable() -> void
	{
		#if LUX_COMPILER(MSVC)
			__assume(false);
		#elif LUX_COMPILER(CLANG) or LUX_COMPILER(GCC)
			__builtin_unreachable();
		#endif
	}
}
