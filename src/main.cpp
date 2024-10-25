#include <Luz/Core/PlatformMacros.hpp>
#include <iostream>

auto main() -> int
{
	std::cout << "bonjour" << std::endl;

	std::cout << "windows: " << LUZ_OS(WINDOWS) << std::endl;
	std::cout << "linux: " << LUZ_OS(LINUX) << std::endl;
	std::cout << "mac: " << LUZ_OS(MAC) << std::endl;

	std::cout << "clang: " << LUZ_COMPILER(CLANG) << std::endl;
	std::cout << "gcc: " << LUZ_COMPILER(GCC) << std::endl;
	std::cout << "msvc: " << LUZ_COMPILER(MSVC) << std::endl;
}
