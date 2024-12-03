#include <Lux/Log/Log.hpp>
#include <Lux/Core/PlatformMacros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <compare>
#include <string_view>
#include <vector>
#include <array>

struct Location
{
	std::uint_least32_t line;
	std::uint_least32_t column;
	std::string_view filename;
	std::string_view function;

	auto operator==(Location const&) const -> bool = default;
};

struct Log
{
	lux::log::Level level;
	Location location;
	std::string str;

	auto operator==(Log const&) const -> bool = default;
};

struct TestLogger : lux::log::Logger
{
	auto LogImpl(lux::log::Level level, std::source_location const& location, std::string_view str) -> void override
	{
		logs.push_back({
			.level = level,
			.location = {
				.line = location.line(),
				.column = location.column(),
				.filename = location.file_name(),
				.function = location.function_name(),
			},
			.str = std::string(str),
		});
	}

	std::vector<::Log> logs;
};

TEST_CASE("Logger", "[Log]")
{
	SECTION("only logs below the level are logged")
	{
		auto logger = TestLogger();
		logger.SetLevel(lux::log::Level::All);

		logger.Log(lux::log::Level::Error, {}, "error");
		logger.Log(lux::log::Level::Warn, {}, "warn");
		logger.Log(lux::log::Level::Info, {}, "info");
		logger.Log(lux::log::Level::Debug, {}, "debug");
		logger.Log(lux::log::Level::Trace, {}, "trace");

		CHECK(logger.logs[0] == Log { lux::log::Level::Error, {}, "error" });
		CHECK(logger.logs[1] == Log { lux::log::Level::Warn, {}, "warn" });
		CHECK(logger.logs[2] == Log { lux::log::Level::Info, {}, "info" });
		CHECK(logger.logs[3] == Log { lux::log::Level::Debug, {}, "debug" });
		CHECK(logger.logs[4] == Log { lux::log::Level::Trace, {}, "trace" });

		logger.SetLevel(lux::log::Level::Warn);

		logger.Log(lux::log::Level::Error, {}, "error");
		logger.Log(lux::log::Level::Warn, {}, "warn");
		logger.Log(lux::log::Level::Info, {}, "info");
		logger.Log(lux::log::Level::Debug, {}, "debug");
		logger.Log(lux::log::Level::Trace, {}, "trace");

		CHECK(logger.logs[5] == Log { lux::log::Level::Error, {}, "error" });
		CHECK(logger.logs[6] == Log { lux::log::Level::Warn, {}, "warn" });
	}
}

TEST_CASE("Log", "[Log]")
{
	auto logger = TestLogger();
	lux::log::SetLogger(&logger);
	CHECK(&lux::log::GetLogger() == &logger);

	SECTION("log functions")
	{
		lux::log::Log(lux::log::Level::Info, {}, "salut");
		CHECK(logger.logs[0] == Log { lux::log::Level::Info, {}, "salut" });

		lux::log::Logf(lux::log::Level::Info, {}, "info: {}", "salut");
		CHECK(logger.logs[1] == Log { lux::log::Level::Info, {}, "info: salut" });
	}

	SECTION("log macros")
	{
		LUX_LOG_ERROR("error");
		LUX_LOG_WARN("warn");
		LUX_LOG_INFO("info");
		LUX_LOG_DEBUG("debug");
		LUX_LOG_TRACE("trace");

		LUX_LOG_INFO("formatted {}: {}", "info", 42);

#if LUX_COMPILER(MSVC)
		auto filename = "tests\\Log\\LogTest.cpp";
		auto function = "void __cdecl CATCH2_INTERNAL_TEST_3(void)";
#else
		auto filename = "tests/Log/LogTest.cpp";
		auto function = "void CATCH2_INTERNAL_TEST_3()";
#endif

#if LUX_COMPILER(CLANG)
		auto columns = std::array { 24u, 22u, 22u, 24u, 24u, 46u };
#else
		auto columns = std::array { 3u, 3u, 3u, 3u, 3u, 3u };
#endif

		CHECK(logger.logs[0] == Log {
			lux::log::Level::Error,
			{ 97, columns[0], filename, function },
			"error"
		});

		CHECK(logger.logs[1] == Log {
			lux::log::Level::Warn,
			{ 98, columns[1], filename, function },
			"warn"
		});

		CHECK(logger.logs[2] == Log {
			lux::log::Level::Info,
			{ 99, columns[2], filename, function },
			"info"
		});

		CHECK(logger.logs[3] == Log {
			lux::log::Level::Debug,
			{ 100, columns[3], filename, function },
			"debug"
		});

		CHECK(logger.logs[4] == Log {
			lux::log::Level::Trace,
			{ 101, columns[4], filename, function },
			"trace"
		});

		CHECK(logger.logs[5] == Log {
			lux::log::Level::Info,
			{ 103, columns[5], filename, function },
			"formatted info: 42"
		});
	}
}
