#include <Lux/Core/PlatformMacros.hpp>
#include <Lux/Core/Debug.hpp>
#include <Lux/Core/Wtf.hpp>
#include <Lux/Core/Version.hpp>
#include <Lux/Log/Log.hpp>
#include <iostream>

auto main() -> int
{
	std::cout << "bonjour" << std::endl;

	std::cout << "windows: " << LUX_OS(WINDOWS) << std::endl;
	std::cout << "linux: " << LUX_OS(LINUX) << std::endl;
	std::cout << "mac: " << LUX_OS(MAC) << std::endl;

	std::cout << "clang: " << LUX_COMPILER(CLANG) << std::endl;
	std::cout << "gcc: " << LUX_COMPILER(GCC) << std::endl;
	std::cout << "msvc: " << LUX_COMPILER(MSVC) << std::endl;

	LUX_ASSERT(true, "true");

	LUX_LOG_INFO("salut {}", 42);

	try
	{
		lux::Wtf("something {} happened", "bad");
	}
	catch (lux::Exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	constexpr auto version = lux::GetVersion();
	std::cout << "Version: " << version.major << '.' << version.minor << '.' << version.patch << std::endl;
}
