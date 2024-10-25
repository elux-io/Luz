#pragma once

/**
 * Compiler detection
 */
#define LUZ_COMPILER(name) LUZ_PRIVATE_COMPILER_##name()

#if defined(__clang__)
	#define LUZ_PRIVATE_COMPILER_CLANG() 1
#else
	#define LUZ_PRIVATE_COMPILER_CLANG() 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
	#define LUZ_PRIVATE_COMPILER_GCC() 1
#else
	#define LUZ_PRIVATE_COMPILER_GCC() 0
#endif

#if defined(_MSC_VER)
	#define LUZ_PRIVATE_COMPILER_MSVC() 1
#else
	#define LUZ_PRIVATE_COMPILER_MSVC() 0
#endif

#if !LUZ_COMPILER(CLANG) && \
    !LUZ_COMPILER(GCC) && \
    !LUZ_COMPILER(MSVC)
#pragma message("unknown compiler")
#endif

/**
 * OS detection
 */
#define LUZ_OS(name) LUZ_PRIVATE_OS_##name()

#if defined(_WIN32)
	#define LUZ_PRIVATE_OS_WINDOWS() 1
#else
	#define LUZ_PRIVATE_OS_WINDOWS() 0
#endif

#if defined(__linux__)
	#define LUZ_PRIVATE_OS_LINUX() 1
#else
	#define LUZ_PRIVATE_OS_LINUX() 0
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#define LUZ_PRIVATE_OS_MAC() 1
#else
	#define LUZ_PRIVATE_OS_MAC() 0
#endif

#if !LUZ_OS(WINDOWS) && \
    !LUZ_OS(LINUX) && \
    !LUZ_OS(MAC)
#pragma message("unknown OS")
#endif
