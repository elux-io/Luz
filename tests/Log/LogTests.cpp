#include <Luz/Log/Log.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <compare>
#include <string_view>
#include <vector>

struct Location
{
	auto operator==(const Location&) const -> bool = default;

	std::uint_least32_t line;
	std::uint_least32_t column;
	std::string_view filename;
	std::string_view function;
};

struct Log
{
	auto operator==(const Log&) const -> bool = default;

	luz::log::Level level;
	Location location;
	std::string str;
};

struct TestLogger : luz::log::Logger
{
	auto LogImpl(luz::log::Level level, const std::source_location& location, std::string_view str) -> void override
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
		logger.SetLevel(luz::log::Level::All);

		logger.Log(luz::log::Level::Error, {}, "error");
		logger.Log(luz::log::Level::Warn, {}, "warn");
		logger.Log(luz::log::Level::Info, {}, "info");
		logger.Log(luz::log::Level::Debug, {}, "debug");
		logger.Log(luz::log::Level::Trace, {}, "trace");

		CHECK(logger.logs[0] == Log { luz::log::Level::Error, {}, "error" });
		CHECK(logger.logs[1] == Log { luz::log::Level::Warn, {}, "warn" });
		CHECK(logger.logs[2] == Log { luz::log::Level::Info, {}, "info" });
		CHECK(logger.logs[3] == Log { luz::log::Level::Debug, {}, "debug" });
		CHECK(logger.logs[4] == Log { luz::log::Level::Trace, {}, "trace" });

		logger.SetLevel(luz::log::Level::Warn);

		logger.Log(luz::log::Level::Error, {}, "error");
		logger.Log(luz::log::Level::Warn, {}, "warn");
		logger.Log(luz::log::Level::Info, {}, "info");
		logger.Log(luz::log::Level::Debug, {}, "debug");
		logger.Log(luz::log::Level::Trace, {}, "trace");

		CHECK(logger.logs[5] == Log { luz::log::Level::Error, {}, "error" });
		CHECK(logger.logs[6] == Log { luz::log::Level::Warn, {}, "warn" });
	}
}

TEST_CASE("Log", "[Log]")
{
	auto logger = TestLogger();
	luz::log::SetLogger(&logger);
	CHECK(&luz::log::GetLogger() == &logger);

	SECTION("log functions")
	{
		luz::log::Log(luz::log::Level::Info, {}, "salut");
		CHECK(logger.logs[0] == Log { luz::log::Level::Info, {}, "salut" });

		luz::log::Logf(luz::log::Level::Info, {}, "info: {}", "salut");
		CHECK(logger.logs[1] == Log { luz::log::Level::Info, {}, "info: salut" });
	}

	SECTION("log macros")
	{
		LUZ_LOG_ERROR("error");
		LUZ_LOG_WARN("warn");
		LUZ_LOG_INFO("info");
		LUZ_LOG_DEBUG("debug");
		LUZ_LOG_TRACE("trace");

		LUZ_LOG_INFO("formatted {}: {}", "info", 42);

		CHECK(logger.logs[0] == Log {
			luz::log::Level::Error,
			{ 95, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"error"
		});
		CHECK(logger.logs[1] == Log {
			luz::log::Level::Warn,
			{ 96, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"warn"
		});
		CHECK(logger.logs[2] == Log {
			luz::log::Level::Info,
			{ 97, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"info"
		});
		CHECK(logger.logs[3] == Log {
			luz::log::Level::Debug,
			{ 98, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"debug"
		});
		CHECK(logger.logs[4] == Log {
			luz::log::Level::Trace,
			{ 99, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"trace"
		});
		CHECK(logger.logs[5] == Log {
			luz::log::Level::Info,
			{ 101, 3, "tests\\Log\\LogTests.cpp", "void __cdecl CATCH2_INTERNAL_TEST_3(void)" },
			"formatted info: 42"
		});
	}
}
