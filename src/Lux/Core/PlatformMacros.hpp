#pragma once

/**
 * Compiler detection
 */
#define LUX_COMPILER(name) LUX_PRIVATE_COMPILER_##name()

#if defined(__clang__)
	#define LUX_PRIVATE_COMPILER_CLANG() 1
#else
	#define LUX_PRIVATE_COMPILER_CLANG() 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
	#define LUX_PRIVATE_COMPILER_GCC() 1
#else
	#define LUX_PRIVATE_COMPILER_GCC() 0
#endif

#if defined(_MSC_VER)
	#define LUX_PRIVATE_COMPILER_MSVC() 1
#else
	#define LUX_PRIVATE_COMPILER_MSVC() 0
#endif

#if !LUX_COMPILER(CLANG) && \
    !LUX_COMPILER(GCC) && \
    !LUX_COMPILER(MSVC)
#pragma message("unknown compiler")
#endif

/**
 * OS detection
 */
#define LUX_OS(name) LUX_PRIVATE_OS_##name()

#if defined(_WIN32)
	#define LUX_PRIVATE_OS_WINDOWS() 1
#else
	#define LUX_PRIVATE_OS_WINDOWS() 0
#endif

#if defined(__linux__)
	#define LUX_PRIVATE_OS_LINUX() 1
#else
	#define LUX_PRIVATE_OS_LINUX() 0
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#define LUX_PRIVATE_OS_MAC() 1
#else
	#define LUX_PRIVATE_OS_MAC() 0
#endif

#if !LUX_OS(WINDOWS) && \
    !LUX_OS(LINUX) && \
    !LUX_OS(MAC)
#pragma message("unknown OS")
#endif
