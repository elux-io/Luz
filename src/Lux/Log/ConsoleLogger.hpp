#pragma once

#include "Logger.hpp"

namespace lux::log
{
	class ConsoleLogger final : public Logger
	{
	private:
		auto LogImpl(Level level, std::source_location const& location, std::string_view str) -> void override;
	};
}
