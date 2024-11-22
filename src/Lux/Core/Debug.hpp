#pragma once

#include "PlatformMacros.hpp"

#include <Lux/Log/Log.hpp>

#if LUX_COMPILER(MSVC)
	#define LUX_DEBUG_BREAK() (__debugbreak())
#elif LUX_COMPILER(CLANG) or LUX_COMPILER(GCC)
	#define LUX_DEBUG_BREAK() (__builtin_trap())
#else
	#define LUX_DEBUG_BREAK() ((void)0)
#endif

#if not defined(NDEBUG)
	#define LUX_ASSERT(expr, ...) ((expr) or (::lux::detail::DO_NOT_PAY_ATTENTION_TO_WHATEVER_THE_HELL_THE_COMPILER_IS_SAYING__THIS_ERROR_IS_CAUSED_BY_A_FAILED_ASSERT(), LUX_LOG_ERROR("assertion `" #expr "` failed" __VA_OPT__(": ") __VA_ARGS__), LUX_DEBUG_BREAK(), false))
#else
	#define LUX_ASSERT(...) ((void)0)
#endif

namespace lux
{
	namespace detail
	{
		inline auto DO_NOT_PAY_ATTENTION_TO_WHATEVER_THE_HELL_THE_COMPILER_IS_SAYING__THIS_ERROR_IS_CAUSED_BY_A_FAILED_ASSERT() {}
	}

	[[noreturn]] inline auto Unreachable() -> void
	{
		LUX_LOG_ERROR("unreachable code reached");
		LUX_DEBUG_BREAK();

		#if LUX_COMPILER(MSVC)
			__assume(false);
		#elif LUX_COMPILER(CLANG) or LUX_COMPILER(GCC)
			__builtin_unreachable();
		#endif
	}
}
