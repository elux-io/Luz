#pragma once

#include "Level.hpp"
#include "Logger.hpp"

#include <format>
#include <string_view>
#include <source_location>

#if LUZ_MAX_LOG_LEVEL >= LUZ_LOG_LEVEL(ERROR)
	#define LUZ_LOG_ERROR(fmt, ...) ::luz::log::Log##__VA_OPT__(f)(::luz::log::Level::Error, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUZ_LOG_ERROR(...)
#endif

#if LUZ_MAX_LOG_LEVEL >= LUZ_LOG_LEVEL(WARN)
	#define LUZ_LOG_WARN(fmt, ...) ::luz::log::Log##__VA_OPT__(f)(::luz::log::Level::Warn, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUZ_LOG_WARN(...)
#endif

#if LUZ_MAX_LOG_LEVEL >= LUZ_LOG_LEVEL(INFO)
	#define LUZ_LOG_INFO(fmt, ...) ::luz::log::Log##__VA_OPT__(f)(::luz::log::Level::Info, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUZ_LOG_INFO(...)
#endif

#if LUZ_MAX_LOG_LEVEL >= LUZ_LOG_LEVEL(DEBUG)
	#define LUZ_LOG_DEBUG(fmt, ...) ::luz::log::Log##__VA_OPT__(f)(::luz::log::Level::Debug, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUZ_LOG_DEBUG(...)
#endif

#if LUZ_MAX_LOG_LEVEL >= LUZ_LOG_LEVEL(TRACE)
	#define LUZ_LOG_TRACE(fmt, ...) ::luz::log::Log##__VA_OPT__(f)(::luz::log::Level::Trace, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUZ_LOG_TRACE(...)
#endif

namespace luz::log
{
	auto GetLogger() -> Logger&;
	auto SetLogger(Logger* logger) -> void;

	inline auto Log(Level level, std::source_location const& location, std::string_view str) -> void
	{
		GetLogger().Log(level, location, str);
	}

	template<typename... Args>
	auto Logf(Level level, std::source_location const& location, std::format_string<Args...> fmt, Args&&... args) -> void
	{
		GetLogger().Log(level, location, std::vformat(fmt.get(), std::make_format_args(args...)));
	}
}
