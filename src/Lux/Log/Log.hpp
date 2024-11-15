#pragma once

#include "Level.hpp"
#include "Logger.hpp"

#include <format>
#include <string_view>
#include <source_location>

#if LUX_MAX_LOG_LEVEL >= LUX_LOG_LEVEL(ERROR)
	#define LUX_LOG_ERROR(fmt, ...) ::lux::log::Log##__VA_OPT__(f)(::lux::log::Level::Error, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUX_LOG_ERROR(...)
#endif

#if LUX_MAX_LOG_LEVEL >= LUX_LOG_LEVEL(WARN)
	#define LUX_LOG_WARN(fmt, ...) ::lux::log::Log##__VA_OPT__(f)(::lux::log::Level::Warn, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUX_LOG_WARN(...)
#endif

#if LUX_MAX_LOG_LEVEL >= LUX_LOG_LEVEL(INFO)
	#define LUX_LOG_INFO(fmt, ...) ::lux::log::Log##__VA_OPT__(f)(::lux::log::Level::Info, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUX_LOG_INFO(...)
#endif

#if LUX_MAX_LOG_LEVEL >= LUX_LOG_LEVEL(DEBUG)
	#define LUX_LOG_DEBUG(fmt, ...) ::lux::log::Log##__VA_OPT__(f)(::lux::log::Level::Debug, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUX_LOG_DEBUG(...)
#endif

#if LUX_MAX_LOG_LEVEL >= LUX_LOG_LEVEL(TRACE)
	#define LUX_LOG_TRACE(fmt, ...) ::lux::log::Log##__VA_OPT__(f)(::lux::log::Level::Trace, ::std::source_location::current(), fmt __VA_OPT__(,) __VA_ARGS__)
#else
	#define LUX_LOG_TRACE(...)
#endif

namespace lux::log
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
