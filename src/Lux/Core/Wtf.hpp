#pragma once

#include <Lux/Log/Log.hpp>
#include <format>
#include <stdexcept>

namespace lux
{
	class Exception : public std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};

	template<typename... Args>
	[[noreturn]] auto Wtf(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		auto str = std::vformat(fmt.get(), std::make_format_args(args...));
		LUX_LOG_ERROR("wtf: {}", str);

		throw Exception(std::move(str));
	}
}
