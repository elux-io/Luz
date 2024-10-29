#pragma once

#include "Logger.hpp"

namespace luz::log
{
	class ConsoleLogger final : public Logger
	{
	private:
		auto LogImpl(Level level, const std::source_location& location, std::string_view str) -> void override;
	};
}
