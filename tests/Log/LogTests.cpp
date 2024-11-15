#include <Lux/Log/Log.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <compare>
#include <string_view>
#include <vector>

struct Location
{
	auto operator==(Location const&) const -> bool = default;

	std::uint_least32_t line;
	std::uint_least32_t column;
	std::string_view filename;
	std::string_view function;
};

struct Log
{
	auto operator==(Log const&) const -> bool = default;

	lux::log::Level level;
	Location location;
	std::string str;
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

		CHECK(logger.logs[0] == Log {
			lux::log::Level::Error,
			{ 95, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"error"
		});
		CHECK(logger.logs[1] == Log {
			lux::log::Level::Warn,
			{ 96, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"warn"
		});
		CHECK(logger.logs[2] == Log {
			lux::log::Level::Info,
			{ 97, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"info"
		});
		CHECK(logger.logs[3] == Log {
			lux::log::Level::Debug,
			{ 98, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"debug"
		});
		CHECK(logger.logs[4] == Log {
			lux::log::Level::Trace,
			{ 99, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"trace"
		});
		CHECK(logger.logs[5] == Log {
			lux::log::Level::Info,
			{ 101, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"formatted info: 42"
		});
	}
}
