#pragma once

#include <Luz/Log/Log.hpp>
#include <format>
#include <stdexcept>

namespace luz
{
	class Exception : public std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};

	template<typename... Args>
	[[noreturn]] auto Wtf(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		auto str = std::vformat(fmt.get(), std::make_format_args(args...));
		LUZ_LOG_ERROR("wtf: {}", str);

		throw Exception(std::move(str));
	}
}
